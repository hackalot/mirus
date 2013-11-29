# Copyright 2013 Joshua Beitler

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

# http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# dependencies
require 'rubygems'

begin
  require 'colorize'
rescue Gem::LoadError
  # not installed
end

require './build/lib/deps'

# check for required programs
if meets_deps? == false
    puts "Does not meet dependencies, cannot continue.".red
    exit -1
end

# require all our tasks
require './build/lib/env'
require './build/lib/tasks/all'
require './build/lib/tasks/iso'
require './build/lib/tasks/asm'
require './build/lib/tasks/clean'
require './build/lib/tasks/kernel'
require './build/lib/tasks/qemu'
require './build/lib/tasks/link'
require './build/lib/tasks/ramdisk'

directory "./build/logs"

# default task is to generate an iso image
task :default => ['make_iso'] do
    if $errors
        puts
        puts "[rake] Errors were generated during the build.  Please review the \"build/*.log\" files for details.".red
        exit 1
    else
        puts
        puts "[rake] Build completed successfully!".green
        exit 0
    end
end
