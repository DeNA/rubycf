require 'tests_helper'

class TestPlistReading < Test::Unit::TestCase

  context "PList decoding" do
    
    should "be able to open a basic string plist." do
      assert_equal 'Just a String', RubyCF::PList.parse(File.read('test/test_assets/String.plist'))
    end
    
    should "be able to open a basic Number plist" do
      assert_equal 1337, RubyCF::PList.parse_file('test/test_assets/Integer.plist')
      assert_equal 1337.4, RubyCF::PList.parse_file(File.open('test/test_assets/Float.plist'))
    end

    should "be able to open a basic Date plist" do
      # This isn't 100% accurate.  If you need subsecond accuracy, cfdate.c needs to be reworked.
      assert_equal Time.mktime(2008, "dec", 25).ctime, RubyCF::PList.parse(File.read('test/test_assets/Date.plist')).ctime
    end

    should "be able to open a basic Boolean plist" do
      assert_equal true, RubyCF::PList.parse(File.read('test/test_assets/Boolean.plist'))
    end

    should "be able to open a Data plist" do
      assert_equal RubyCF::Data.from_file('test/test_assets/photo.jpg'), RubyCF::PList.parse_file('test/test_assets/Data.plist')
    end
    
    should "be able to open a Dictionary plist" do
      assert_equal({'STRING' => 'A', 'INT' => 2, 'BOOL' => false, 'FLOAT' => 10.1}, RubyCF::PList.parse(File.read('test/test_assets/Dictionary.plist')))
    end
    
    should "be able to open an Array plist" do
      assert_equal([false, 10.1, 2, 'A'], RubyCF::PList.parse(File.read('test/test_assets/Array.plist')))
    end
    
    should "be able to open a plist with multiple, nested structures." do
      struct = {
        'array' => [1, 2, 3, 4],
        'hash' => {'foo' => 'bar', 'baz' => 10.4}
      }
      assert_equal(struct, RubyCF::PList.parse(File.read('test/test_assets/Complex.plist')))
      
    end

    should "be marked tainted" do
      assert(RubyCF::PList.parse(File.read('test/test_assets/Array.plist')).tainted?, 'Array')
      assert(RubyCF::PList.parse(File.read('test/test_assets/Data.plist')).tainted?, 'Data')
      assert(RubyCF::PList.parse(File.read('test/test_assets/Dictionary.plist')).tainted?, 'Dictionary')
      assert(RubyCF::PList.parse(File.read('test/test_assets/String.plist')).tainted?, 'String')
    end
    
  end

end