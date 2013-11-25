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

# build assembly
desc "Build bootstrap + lower level ASM code"
task :build_asm do
    puts "  __  __ ___ ___ _   _ ___ "
    puts " |  \\/  |_ _| _ | | | / __|"
    puts " | |\\/| || ||   | |_| \\__ \\"
    puts " |_|  |_|___|_|_\\\\___/|___/"
    puts

    puts "[rake] Assembling"
    $asm_files.each do |t|
        # replace .asm with .o
        object_file = t.sub(/\.asm$/, '.o')
        
        # assemble + get status
        sh "#{$assembler} #{$assembler_flags} -o #{object_file} #{t} >>./build/logs/asmlog.log 2>&1" do |ok, res|
            if ! ok
                puts "[rake] Could not build #{t}".red
                $errors = true
            else
                puts "    --> #{t}"
            end
        end
    end
    puts
end