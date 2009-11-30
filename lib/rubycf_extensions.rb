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