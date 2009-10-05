#include <ruby.h>
#include <CoreFoundation/CFString.h>

VALUE rbcf_string_convert_to_ruby(CFStringRef string_ref);
CFStringRef rbcf_string_convert_to_cf(VALUE string);