#  Copyright (c) 2009 ngmoco:)
#  
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#  
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#  
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.

require 'tests_helper'

class TestRubyConvenienceMethods < Test::Unit::TestCase
  context "Ruby convenience methods" do
    
    should "be able to encode a basic string plist" do
      string = "Just a String"
      encoded = string.to_plist
      assert_equal string, RubyCF::PList.parse(encoded)
    end

    should "be able to encode a basic number plist" do
      int_val, float_val = 10, 10.1
      assert_equal int_val, RubyCF::PList.parse(int_val.to_plist)
      assert_equal float_val, RubyCF::PList.parse(float_val.to_plist)
    end
    
    should "be able to encode a basic Date plist" do
      # This isn't 100% accurate.  If you need subsecond accuracy, cfdate.c needs to be reworked.
      time = Time.mktime(2008, "dec", 25)
      assert_equal time.ctime, RubyCF::PList.parse(time.to_plist).ctime
    end
    
    should "be able to encode raw data" do
      data = RubyCF::Data.from_file('test/test_assets/photo.jpg')
      assert_equal data, RubyCF::PList.parse(data.to_plist)
    end
    
    should "be able to encode an array" do
      array = ["foo", "bar", "baz"]
      array2 = [10, 1.2, 500.72]
      array3 = ["foo", false, 3434]
      assert_equal array, RubyCF::PList.parse(array.to_plist)
      assert_equal array2, RubyCF::PList.parse(array2.to_plist)
      assert_equal array3, RubyCF::PList.parse(array3.to_plist)
    end
    
    should "be able to encode hashes" do
      hash = {"a"=>'foo', 'b'=>'baz'}
      hash2 = {:foo=>'bar',:boo=>'bar'} #symbols will be converted to strings
      hash3 = {'stuff'=>123, 'false'=>false, 'bar'=>'bax', 'float'=>12.2}
      assert_equal hash, RubyCF::PList.parse(hash.to_plist)
      assert_equal({'foo'=>'bar','boo'=>'bar'}, RubyCF::PList.parse(hash2.to_plist))
      assert_equal hash3, RubyCF::PList.parse(hash3.to_plist)
    end
    
  end
end