#import "cfarray.h"
#import "plist.h"

VALUE rbcf_array_convert_to_ruby(CFArrayRef array_ref) {

    CFIndex count = CFArrayGetCount(array_ref);
    CFIndex i = 0;
    
    VALUE array = rb_ary_new();
    
    for(i=0; i < count; ++i){
        rb_ary_push(array, rbcf_plist_convert_to_ruby(CFArrayGetValueAtIndex(array_ref, i)));
    }

    OBJ_TAINT(array);
    
    return array;
}

CFArrayRef rbcf_array_convert_to_cf(VALUE array) {
    CFIndex size = FIX2INT(rb_funcall(array, rb_intern("size"), 0));
    CFIndex i;
    CFTypeRef *values = (CFTypeRef *)malloc(size * sizeof(CFTypeRef));
    for(i = 0; i < size; ++i){
        values[i] = rbcf_plist_convert_to_cf(rb_ary_entry(array, i));
    }
    
    CFArrayRef newArray = CFArrayCreate(kCFAllocatorDefault, values, size, &kCFTypeArrayCallBacks);
    rbcf_register_for_release(newArray);
    
    return newArray;
}