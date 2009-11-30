require 'rubygems'
require 'rake/gempackagetask'
require 'rake/testtask'
require 'rake/clean'

CLEAN.include('*.o')
CLEAN.include('Makefile')
CLOBBER.include('rubycf.bundle')

# load gemspec
$gemspec = File.open(File.join(Dir.pwd, 'rubycf.gemspec'), 'r'){|f| eval(f.read)}

desc "Compile the library"
task :build do
  puts `ruby extconf.rb && make --always-make`
  raise 'Build failed' unless $? == 0
end

desc "Compile and install the library"
task :install => [:build] do
  `make install`
end

Rake::GemPackageTask.new($gemspec) do |pkg| 
  pkg.need_tar = true 
end

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/test_*.rb']
  t.verbose = true
end

task :test => [:build]

