require 'tests_helper'

class TestPlistReading < Test::Unit::TestCase
  context "PList encoding" do
    
    should "be able to encode a basic string plist" do
      string = "Just a String"
      encoded = RubyCF::PList.encode(string)
      assert_equal string, RubyCF::PList.parse(encoded)
    end

    should "be able to encode a basic number plist" do
      int_val, float_val = 10, 10.1
      assert_equal int_val, RubyCF::PList.parse(RubyCF::PList.encode(int_val))
      assert_equal float_val, RubyCF::PList.parse(RubyCF::PList.encode(float_val))
    end
    
    should "be able to encode a basic boolean plist" do
      assert_equal true, RubyCF::PList.parse(RubyCF::PList.encode(true))
      assert_equal false, RubyCF::PList.parse(RubyCF::PList.encode(false))
    end

    should "be able to encode a basic Date plist" do
      # This isn't 100% accurate.  If you need subsecond accuracy, cfdate.c needs to be reworked.
      time = Time.mktime(2008, "dec", 25)
      assert_equal time.ctime, RubyCF::PList.parse(RubyCF::PList.encode(time)).ctime
    end
    
    should "be able to encode raw data" do
      data = RubyCF::Data.from_file('test/test_assets/photo.jpg')
      assert_equal data, RubyCF::PList.parse(RubyCF::PList.encode(data))
    end
    
    should "be able to encode an array" do
      array = ["foo", "bar", "baz"]
      array2 = [10, 1.2, 500.72]
      array3 = ["foo", false, 3434]
      assert_equal array, RubyCF::PList.parse(RubyCF::PList.encode(array))
      assert_equal array2, RubyCF::PList.parse(RubyCF::PList.encode(array2))
      assert_equal array3, RubyCF::PList.parse(RubyCF::PList.encode(array3))
    end
    
    should "be able to encode hashes" do
      hash = {"a"=>'foo', 'b'=>'baz'}
      hash2 = {:foo=>'bar',:boo=>'bar'} #symbols will be converted to strings
      hash3 = {'stuff'=>123, 'false'=>false, 'bar'=>'bax', 'float'=>12.2}
      assert_equal hash, RubyCF::PList.parse(RubyCF::PList.encode(hash))
      assert_equal({'foo'=>'bar','boo'=>'bar'}, RubyCF::PList.parse(RubyCF::PList.encode(hash2)))
      assert_equal hash3, RubyCF::PList.parse(RubyCF::PList.encode(hash3))
    end
    
    should "be able to encode objects that respond to to_hash" do
      hash = {"a"=>'foo', 'b'=>'baz'}
      obj = HashEncodeableClass.new(hash)
      assert_equal hash, RubyCF::PList.decode(obj.to_plist)
      
      # embedded version
      hash2 = {'boo' => 123, 'stuff' => obj}
      assert_equal hash2.dup.merge('stuff' => hash2['stuff'].to_hash), RubyCF::PList.parse(hash2.to_plist)
    end
    
    should "be able to encode objects that respond to to_a" do
      hash = %w{a be see}
      obj = ArrayEncodeableClass.new(hash)
      assert_equal hash, RubyCF::PList.decode(obj.to_plist)
    end
    
    should "return nil for an unencodable object" do
      assert_equal nil, RubyCF::PList.decode(UnencodableClass.new.to_plist)
    end
    
    should "be able to encode xml property lists" do
      obj = RubyCF::PList.parse_file('test/test_assets/Complex.plist')

      xml_plist = RubyCF::PList.encode(obj, :xml)
      assert_match(/xml/, xml_plist)
      parsed_xml_plist = RubyCF::PList.parse(xml_plist)
      assert_equal(obj, parsed_xml_plist)
      
      xml_plist = obj.to_plist(:xml)
      assert_match(/xml/, xml_plist)
      parsed_xml_plist = RubyCF::PList.parse(xml_plist)
      assert_equal(obj, parsed_xml_plist)
      
    end
    
  end
end