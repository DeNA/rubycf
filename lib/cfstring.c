/*
 *  Copyright (c) 2009 ngmoco:)
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

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