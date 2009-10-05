#import "cfdate.h"

VALUE rbcf_date_convert_to_ruby(CFDateRef date_ref) {
    //fixme: this isn't 100% accurate, but should be close enough
    CFDateRef currentTime = CFDateCreate(NULL, CFAbsoluteTimeGetCurrent());
    CFTimeInterval difference = CFDateGetTimeIntervalSinceDate(date_ref, currentTime);
    
    return rb_funcall(rb_funcall(rb_cTime, rb_intern("now"), 0), rb_intern("+"), 1, rb_float_new(difference));
}

CFDateRef rbcf_date_convert_to_cf(VALUE time) {
    VALUE reference_date = rb_eval_string("Time.gm(2001, 'jan', 1)");
    CFTimeInterval difference = NUM2DBL(rb_funcall(time, rb_intern("-"), 1, reference_date));
    CFDateRef date = CFDateCreate(kCFAllocatorDefault, difference);
    rbcf_register_for_release(date);
    
    return date;
}