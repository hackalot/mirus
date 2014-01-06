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

# create ramdisk
desc "Create the ramdisk"
task :build_ramdisk do
    if ! $errors
    	sh "cd ramdisk && tar -cf ../iso/boot/ramdisk.tar * && cd .. 2>&1"
    else
    	puts
    	puts "Cannot build ramdisk".red
    	exit(1)
    end
end
