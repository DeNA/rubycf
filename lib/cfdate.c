/*
 *  Copyright (c) 2009 ngmoco:)
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

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