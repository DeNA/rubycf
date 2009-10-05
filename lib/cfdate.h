#include <ruby.h>
#include <CoreFoundation/CFDate.h>

VALUE rbcf_date_convert_to_ruby(CFDateRef date_ref);
CFDateRef rbcf_date_convert_to_cf(VALUE time);
