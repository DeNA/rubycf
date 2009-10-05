require 'test/unit'
require 'rubygems'
require 'shoulda'
require File.join(File.dirname(__FILE__), '..', 'rubycf')

# mocks for testing encoding
class HashEncodeableClass
  def initialize(value)
    @value = value
  end
  
  def to_hash
    @value
  end
end

class ArrayEncodeableClass
  def initialize(value)
    @value = value
  end
  
  def to_a
    @value
  end
end

class UnencodableClass
end