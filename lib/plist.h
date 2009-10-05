#include <ruby.h>
#include <CoreFoundation/CFPropertyList.h>

RUBY_EXTERN VALUE rb_cCFData;

VALUE rbcf_plist_parse(VALUE self, VALUE data);
VALUE rbcf_plist_encode(int argc, VALUE *argv, VALUE self);

VALUE rbcf_plist_convert_to_ruby(CFPropertyListRef plist);
CFPropertyListRef rbcf_plist_convert_to_cf(VALUE structure);

void rbcf_register_for_release(CFTypeRef obj);