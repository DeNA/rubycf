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

require 'rubygems'
require 'rake/gempackagetask'
require 'rake/testtask'
require 'rake/rdoctask'
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

Rake::RDocTask.new do |rd|
  rd.main = 'README'
  rd.rdoc_files.include('README', 'lib/**/*.rb', 'lib/rubycf.c')
end

task :test => [:build]

