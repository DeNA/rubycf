#include <ruby.h>
#include <CoreFoundation/CFArray.h>

VALUE rbcf_array_convert_to_ruby(CFArrayRef array_ref);
CFArrayRef rbcf_array_convert_to_cf(VALUE array);