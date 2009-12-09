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