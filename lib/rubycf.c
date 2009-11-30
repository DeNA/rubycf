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

/*
 *  call-seq:
 *      parse(string) -> Object
 *  
 *  Parse a string containing the property list data.  Any of the 
 *  property list formats will work, including the deprecated
 *  OpenStep format.
 */
VALUE rbcf_plist_parse(VALUE self, VALUE data);

/*
 *  call-seq:
 *      encode(Object) -> string
 *      encode(Object, :xml) -> string
 *  
 *  Encode a compatible object into a property list.  The default
 *  format is binary, but you can specify :xml to get the xml format
 *  instead.  The OpenStep format is deprecated by CoreFoundation
 *  and is not available in RubyCF.  
 *  
 *  Compatible formats are:
 *  * RubyCF::Data
 *  * Hash
 *  * Array
 *  * Number
 *  * Time
 *  * Boolean
 *  * anything that responds to to_hash
 */
VALUE rbcf_plist_encode(int argc, VALUE *argv, VALUE self);

void Init_rubycf (void)
{
  // Add the initialization code of your module here.
    rb_mRubyCF = rb_define_module("RubyCF");
    
    /*
     *  Methods for encoding and decoding property lists
     */
    rb_cPlist = rb_define_class_under(rb_mRubyCF, "PList", rb_cObject);

    rb_define_module_function(rb_cPlist, "parse", rbcf_plist_parse, 1);
    rb_define_module_function(rb_cPlist, "encode", rbcf_plist_encode, -1);
 
    rb_require("rubycf_extensions.rb");
}
