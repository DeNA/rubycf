require 'tests_helper'

class TestExtensionCreation < Test::Unit::TestCase

  context "Library loading" do
    
    should "load root module" do
      assert_nothing_thrown do 
        RubyCF.methods
      end
    end
    
    should "load classes" do
      %w{PList}.each do |klass_name|
        assert RubyCF.constants.include?(klass_name)
      end
    end
    
    should "load PList class methods" do
      assert RubyCF::PList.respond_to?(:encode)
      assert RubyCF::PList.respond_to?(:parse)
      assert RubyCF::PList.respond_to?(:parse_file)
    end
    
  end

end