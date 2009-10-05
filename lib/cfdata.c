#include "cfdata.h"
#include "plist.h"

VALUE rbcf_data_convert_to_ruby(CFDataRef data_ref) {
    VALUE rubydata = rb_eval_string("RubyCF::Data.new('')");
    rb_funcall(rubydata, rb_intern("data="), 1, rb_str_new((char *)CFDataGetBytePtr(data_ref), CFDataGetLength(data_ref)));
    OBJ_TAINT(rubydata);
    return rubydata;
}


CFDataRef rbcf_data_convert_to_cf(VALUE data_obj) {
    VALUE data_str = rb_iv_get(data_obj, "@data");
    
    CFDataRef outData = CFDataCreate(kCFAllocatorDefault, (UInt8 *)RSTRING(data_str)->ptr, RSTRING(data_str)->len);
    rbcf_register_for_release(outData);
    
    return outData;
}
