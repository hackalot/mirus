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

# build kernel
desc "Build the kernel"
task :build_kernel do
    $cpp_files.each do |s|
        # replace .cpp with .o
        object_file = s.sub(/\.cpp$/, '.o')

        print "#{$compiler} "

 		# compile + get status
        if system("#{$compiler} #{$cpp_flags} -MMD -MP -c #{s} -o #{object_file} >>./build/logs/kernel.log 2>&1")
        	puts "#{s}".green
        else
        	puts "#{s}".red
        	$errors = true
        end
    end
end