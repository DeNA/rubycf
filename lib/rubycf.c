/*
 *  rubycf.c
 *  rubycf
 *
 *  Created by Dave Grijalva on 12/22/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include <ruby.h>
#include <CoreFoundation/CoreFoundation.h>
#include "plist.h"

static VALUE rb_mRubyCF;
static VALUE rb_cPlist;

void Init_rubycf (void)
{
  // Add the initialization code of your module here.
    rb_mRubyCF = rb_define_module("RubyCF");

    rb_cPlist = rb_define_class_under(rb_mRubyCF, "PList", rb_cObject);
    rb_define_module_function(rb_cPlist, "parse", rbcf_plist_parse, 1);
    rb_define_module_function(rb_cPlist, "encode", rbcf_plist_encode, -1);
 
    rb_require("rubycf_extensions.rb");
}
