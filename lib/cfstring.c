#include "cfstring.h"

VALUE rbcf_string_convert_to_ruby(CFStringRef string_ref) {

    char *buffer;
    CFIndex bufferSize = CFStringGetLength(string_ref) + 1;
    VALUE rubystring;

    buffer = malloc(bufferSize + 1);

    if(CFStringGetCString(string_ref, buffer, bufferSize, kCFStringEncodingASCII)){
        rubystring = rb_str_new2(buffer);
        OBJ_TAINT(rubystring);
    }
    else{
        rubystring = Qnil;
    }

    free(buffer);
    return rubystring;
}

CFStringRef rbcf_string_convert_to_cf(VALUE string) {
    
    CFIndex num_bytes;
    char *bytes = rb_str2cstr(string, &num_bytes);
    CFStringRef cfstring = CFStringCreateWithBytes(kCFAllocatorDefault, (UInt8 *)bytes, num_bytes, kCFStringEncodingASCII, false);
    rbcf_register_for_release(cfstring);
    return cfstring;
}