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