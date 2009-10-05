#import "cfdictionary.h"
#import "plist.h"
#import "cfstring.h"

VALUE rbcf_dict_convert_to_ruby(CFDictionaryRef dict_ref) {
    
    CFIndex count = CFDictionaryGetCount(dict_ref);
    CFIndex i;
    
    CFTypeRef *keys = (CFTypeRef *)malloc(count * sizeof(CFTypeRef));
    CFTypeRef *values = (CFTypeRef *)malloc(count * sizeof(CFTypeRef));
    CFDictionaryGetKeysAndValues(dict_ref, (const void **)keys, (const void **)values);
    
    VALUE hash = rb_hash_new();
    
    for(i=0; i < count; ++i){
        rb_hash_aset(hash, rbcf_string_convert_to_ruby(keys[i]), rbcf_plist_convert_to_ruby(values[i]));
    }
    
    free(keys);
    free(values);

    OBJ_TAINT(hash);
    
    return hash;
}

CFDictionaryRef rbcf_dict_convert_to_cf(VALUE hash) {
    
    VALUE flat_hash = rb_funcall(hash, rb_intern("to_a"), 0);
    CFIndex size = FIX2INT(rb_funcall(hash, rb_intern("size"), 0));
    CFTypeRef *keys = (CFTypeRef *)malloc(size * sizeof(CFTypeRef));
    CFTypeRef *values = (CFTypeRef *)malloc(size * sizeof(CFTypeRef));
    
    CFIndex i;
    for(i = 0; i < size; ++i){
        // Ruby Hash keys can be any object.  Convert keys into strings before using as CFDictionary keys.
        keys[i] = rbcf_plist_convert_to_cf(rb_funcall(rb_ary_entry(rb_ary_entry(flat_hash, i), 0), rb_intern("to_s"), 0));
        values[i] = rbcf_plist_convert_to_cf(rb_ary_entry(rb_ary_entry(flat_hash, i), 1));
    }
    
    CFDictionaryRef dictionary = CFDictionaryCreate(kCFAllocatorDefault, keys, values, size, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    rbcf_register_for_release(dictionary);
    
    free(keys);
    free(values);
    
    return dictionary;
}