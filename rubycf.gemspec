Gem::Specification.new do |s| 
  s.name = "rubycf"
  s.version = "0.2.0"
  s.author = "Dave Grijalva"
  s.email = "dgrijalva@ngmoco.com"
  s.homepage = "http://github.com/ngmoco/rubycf/"
  s.platform = Gem::Platform::RUBY
  s.summary = "Ruby extension for dealing with CoreFoundation types.  Mostly designed for reading and writing xml and binary property lists."
  s.files = FileList["{bin,lib}/**/*"].to_a
  s.require_path = "lib"
  s.autorequire = "rubycf"
  s.test_files = FileList["{test}/**/*test.rb"].to_a
  s.has_rdoc = true
  s.extra_rdoc_files = ["README"]
  s.extensions << 'extconf.rb'
  # s.add_dependency("dependency", ">= 0.x.x")
end
