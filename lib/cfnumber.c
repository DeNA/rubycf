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