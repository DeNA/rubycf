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

#include "cfnumber.h"

VALUE rbcf_boolean_convert_to_ruby(CFBooleanRef bool_ref) {
    if(bool_ref == kCFBooleanTrue){
        return Qtrue;
    }
    else {
        return Qfalse;
    }
}

VALUE rbcf_number_convert_to_ruby(CFNumberRef number_ref) {
    if(CFNumberIsFloatType(number_ref)){
        double value = 0.0;
        if(CFNumberGetValue(number_ref, kCFNumberDoubleType, &value)){
            return rb_float_new(value);
        }
    }
    else{
        long value = 0;
        if(CFNumberGetValue(number_ref, kCFNumberLongType, &value)){
            return INT2NUM(value);
        }
    }

    return Qnil;
}

CFBooleanRef rbcf_boolean_convert_to_cf(VALUE boolean) {
    if(boolean == Qtrue){
        return kCFBooleanTrue;
    }
    else {
        return kCFBooleanFalse;
    }
}

CFNumberRef rbcf_number_convert_to_cf(VALUE number) {
    if(rb_obj_is_kind_of(number, rb_cInteger) == Qtrue){
        long value = NUM2LONG(number);
        CFNumberRef outnum = CFNumberCreate(kCFAllocatorDefault, kCFNumberLongType, &value);
        rbcf_register_for_release(outnum);
        return outnum;
    }
    else if(rb_obj_is_kind_of(number, rb_cFloat) == Qtrue) {
        double value = NUM2DBL(number);
        CFNumberRef outnum = CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &value);
        rbcf_register_for_release(outnum);
        return outnum;
    }
    else {
        return NULL;
    }
    
}