# Extensions to the build in C functions

module RubyCF
  class PList
    class << self
      alias decode parse
    end

    def self.parse_file file
      self.parse(file.is_a?(File) ? file.read : File.read(file))
    end
  end
  
  # CF handles raw data different from strings.  Ruby treats them the same.
  # use RubyCF::Data objects to tell the plist encoder to treat the objects
  # as data.
  class Data
    attr_reader :data

    def self.from_file file
      Data.new(file.is_a?(File) ? file.read : File.read(file))
    end

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
  def to_plist(type = :binary)
    # supported types
    # [Integer, Float, String, Array, Hash, RubyCF::Data].each do |klass|
      return RubyCF::PList.encode(self, type) #if self.is_a? klass
    # end
    # 
    # if self.resond_to? :to_hash
    # elsif self.resond_to? :to_a
    # elsif self.resond_to?
    # 
  end
end