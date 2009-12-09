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

# Extensions to the build in C functions

module RubyCF

  class PList
    class << self
      alias decode parse
    end

    # Parse a plist from a file path or handle
    def self.parse_file file
      self.parse(file.is_a?(File) ? file.read : File.read(file))
    end
  end
  
  # CF handles raw data different from strings.  Ruby treats them the same.
  # Use RubyCF::Data objects to tell the plist encoder to treat the objects
  # as data.
  class Data
    attr_reader :data

    # Create a RubyCF::Data object from a file path or handle
    def self.from_file file
      Data.new(file.is_a?(File) ? file.read : File.read(file))
    end

    # Create a RubyCF::Data object from a string
    def initialize string
      self.data = string
    end

    def inspect
      "RubyCF::Data #{@data.size} bytes"
    end
    
    def == other
      if(other.is_a?(RubyCF::Data))
        return other.data == @data
      else
        return other == @data
      end
    end
    
    def data= string
      @data = string.to_s
    end
    
  end
end

class Object
  # Shorthand for RubyCF::PList.encode(object, format)
  def to_plist(format = :binary)
      RubyCF::PList.encode(self, format)
  end
end