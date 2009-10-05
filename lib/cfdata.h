#include <ruby.h>
#include <CoreFoundation/CFData.h>

VALUE rbcf_data_convert_to_ruby(CFDataRef data_ref);
CFDataRef rbcf_data_convert_to_cf(VALUE data);
