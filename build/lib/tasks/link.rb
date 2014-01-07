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

# linkage
desc "Link object files to flat binary"
task :link => ['build_asm', 'build_kernel'] do
	print "#{$ld} "

	# compile + get status
    if system("#{$ld} #{$ld_flags} -o ./build/#{$target_bin} #{$object_files} >./build/logs/link.log 2>&1")
    	puts "#{$target_bin}".green
    else
    	puts "#{$target_bin}".red
    	$errors = true
    end
end
