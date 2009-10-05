#include <ruby.h>
#include <CoreFoundation/CFDictionary.h>

VALUE rbcf_dict_convert_to_ruby(CFDictionaryRef dict_ref);
CFDictionaryRef rbcf_dict_convert_to_cf(VALUE hash);