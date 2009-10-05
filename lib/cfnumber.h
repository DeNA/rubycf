#include <ruby.h>
#include <CoreFoundation/CFNumber.h>

VALUE rbcf_boolean_convert_to_ruby(CFBooleanRef bool_ref);
VALUE rbcf_number_convert_to_ruby(CFNumberRef number_ref);

CFBooleanRef rbcf_boolean_convert_to_cf(VALUE boolean);
CFNumberRef rbcf_number_convert_to_cf(VALUE number);