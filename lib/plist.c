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

#include "plist.h"

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFStream.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFArray.h>

#include "cfstring.h"
#include "cfnumber.h"
#include "cfdate.h"
#include "cfdictionary.h"
#include "cfarray.h"
#include "cfdata.h"

void rbcf_reset_release_pool();
static CFMutableArrayRef rbcf_plist_generation_release_pool;

static const void *rbcf_retain(CFAllocatorRef ref, const void *obj){
    CFRetain(obj);
}

static void rbcf_release(CFAllocatorRef ref, const void *obj){
    CFRelease(obj);
}

static const CFArrayCallBacks poolarraycallbacks = {
    0,
    rbcf_retain,
    rbcf_release,
    NULL,
    NULL
};

void rbcf_register_for_release(CFTypeRef obj) {
    if(!rbcf_plist_generation_release_pool){
        rbcf_plist_generation_release_pool = CFArrayCreateMutable(kCFAllocatorDefault, 0, &poolarraycallbacks);
    }
    CFArrayAppendValue(rbcf_plist_generation_release_pool, obj);
    CFRelease(obj);
}

void rbcf_reset_release_pool() {
    if(rbcf_plist_generation_release_pool){
        CFRelease(rbcf_plist_generation_release_pool);
        rbcf_plist_generation_release_pool = NULL;
    }
}

VALUE rbcf_plist_convert_to_ruby(CFPropertyListRef plist) {
    CFTypeID plist_type_id = CFGetTypeID(plist);

    if(plist_type_id == CFStringGetTypeID()){
        return rbcf_string_convert_to_ruby(plist);
    }
    else if(plist_type_id == CFBooleanGetTypeID()){
        return rbcf_boolean_convert_to_ruby(plist);
    }
    else if(plist_type_id == CFNumberGetTypeID()){
        return rbcf_number_convert_to_ruby(plist);
    }
    else if(plist_type_id == CFDateGetTypeID()){
        return rbcf_date_convert_to_ruby(plist);
    }
    else if(plist_type_id == CFDataGetTypeID()){
        return rbcf_data_convert_to_ruby(plist);
    }
    else if(plist_type_id == CFDictionaryGetTypeID()){
        return rbcf_dict_convert_to_ruby(plist);
    }
    else if(plist_type_id == CFArrayGetTypeID()){
        return rbcf_array_convert_to_ruby(plist);
    }
    else{
        return Qnil;
    }
}

CFPropertyListRef rbcf_plist_convert_to_cf(VALUE structure) {
    VALUE out;
    
    if(rb_obj_is_kind_of(structure, rb_cString) == Qtrue){
        return rbcf_string_convert_to_cf(structure);
    }
    else if(structure == Qtrue || structure == Qfalse){
        return rbcf_boolean_convert_to_cf(structure);
    }
    else if(rb_obj_is_kind_of(structure, rb_cNumeric) == Qtrue){
        return rbcf_number_convert_to_cf(structure);
    }
    else if(rb_obj_is_kind_of(structure, rb_cTime) == Qtrue){
        return rbcf_date_convert_to_cf(structure);
    }
    else if(rb_obj_is_kind_of(structure, rb_eval_string("RubyCF::Data")) == Qtrue){
        return rbcf_data_convert_to_cf(structure);
    }
    else if(rb_obj_is_kind_of(structure, rb_cArray) == Qtrue){
        return rbcf_array_convert_to_cf(structure);
    }
    else if(rb_obj_is_kind_of(structure, rb_cHash) == Qtrue){
        return rbcf_dict_convert_to_cf(structure);
    }
    else if(rb_respond_to(structure, rb_intern("to_hash"))){
        return rbcf_dict_convert_to_cf(rb_funcall(structure, rb_intern("to_hash"), 0));
    }
    // default (depricated) behavior of to_a is to return [self], which is not helpful
    else if(rb_respond_to(structure, rb_intern("to_a")) && 
        rb_funcall(out = rb_funcall(structure, rb_intern("to_a"), 0), rb_intern("=="), 1, rb_ary_new3(1, structure)) == Qfalse
    ){
        return rbcf_array_convert_to_cf(out);
    }
    else if(rb_respond_to(structure, rb_intern("to_f"))){
        return rbcf_number_convert_to_cf(rb_funcall(structure, rb_intern("to_f"), 0));
    }
    else if(rb_respond_to(structure, rb_intern("to_int"))){
        return rbcf_number_convert_to_cf(rb_funcall(structure, rb_intern("to_i"), 0));
    }
    else if(rb_respond_to(structure, rb_intern("to_str"))){
        return rbcf_string_convert_to_cf(rb_funcall(structure, rb_intern("to_s"), 0));
    }
    else {
        return NULL;
    }
}


VALUE rbcf_plist_parse(VALUE self, VALUE data) {
    CFPropertyListFormat format; // the format of the plist
    CFStringRef errorString; // Parsing error string

    if(rb_obj_is_kind_of(data, rb_cString) == Qtrue){
        CFReadStreamRef stream = CFReadStreamCreateWithBytesNoCopy(NULL, (UInt8 *)RSTRING(data)->ptr, RSTRING(data)->len, kCFAllocatorNull);

        if(CFReadStreamOpen(stream)){
            CFPropertyListRef plist = CFPropertyListCreateFromStream(NULL, stream, 0, kCFPropertyListImmutable, &format, &errorString);
            CFReadStreamClose(stream);
            CFRelease(stream);
            if(plist){
                VALUE plist_value = rbcf_plist_convert_to_ruby(plist);
                CFRelease(plist);
                rbcf_reset_release_pool();
                return plist_value;
            }

        }
    }

    rbcf_reset_release_pool();
    return Qnil;
}


VALUE rbcf_plist_encode(int argc, VALUE *argv, VALUE self) {
    VALUE structure, encoding;
    rb_scan_args(argc, argv, "11", &structure, &encoding);

    CFPropertyListFormat format;  // the output format of the plist
    if(encoding != Qnil && rb_to_id(encoding) == rb_intern("xml")) {
        format = kCFPropertyListXMLFormat_v1_0;
    }
    else {
        format = kCFPropertyListBinaryFormat_v1_0;
    }
    CFStringRef errorString; // Parsing error string

    CFPropertyListRef cf_structure = rbcf_plist_convert_to_cf(structure);
    CFWriteStreamRef stream = CFWriteStreamCreateWithAllocatedBuffers(kCFAllocatorDefault, kCFAllocatorDefault);
    if(CFWriteStreamOpen(stream)){
        CFIndex num_bytes = CFPropertyListWriteToStream(cf_structure, stream, format, &errorString);
        if(num_bytes > 0){
            CFTypeRef data = CFWriteStreamCopyProperty(stream, kCFStreamPropertyDataWritten);
            rbcf_register_for_release(data);
            CFRelease(stream);
            if(data && CFGetTypeID(data) == CFDataGetTypeID()){
                VALUE out_string = rb_str_new((char *)CFDataGetBytePtr(data), CFDataGetLength(data));
                rbcf_reset_release_pool();
                return out_string;
            }
        }
    }
    
    rbcf_reset_release_pool();
    return Qnil;
}

