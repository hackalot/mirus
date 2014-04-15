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

version_major = 0
version_minor = 1
version_rev   = 6
version_code  = 'firefly'
version_post  = 'dev'

arch = 'i386'
arch_c = '__ARCH_I386__'
target = 'mirus'

cxx = 'clang++'
ld  = 'ld'
asm = 'yasm'

cxx_flags = '-fno-builtin -fno-exceptions -ffreestanding -std=c++11 -m32 -Isource/include '
cxx_flags << "-D#{arch_c} -D__VERSION_MAJOR__=#{version_major} "
cxx_flags << "-D__VERSION_MINOR__=#{version_minor} -D__VERSION_REV__=#{version_rev} "
cxx_flags << "-D__VERSION_CODENAME__=#{version_code} -D__VERSION_POSTFIX__=#{version_post} "
asm_flags = '-f elf'
ld_flags = '-T build/mirus.ld -m elf_i386'

cpp_files = FileList[
    "source/kernel/core/**/*.cpp", 
    "source/kernel/arch/#{arch}/**/*.cpp"]

asm_files = FileList[
    "source/kernel/core/**/*.asm",
    "source/kernel/arch/#{arch}/**/*.asm"]

object_files = FileList[]
errors = false
build_disk_image = true

task :default do
    system('mkdir bin bin/obj 2>&1')

    cpp_files.each do |file|
        object_file = file.sub(/\.cpp$/, '.o')
        object_file = File.basename(object_file << File.extname(object_file))

        if system("#{cxx} #{cxx_flags} -MMD -MP -c #{file} -o bin/obj/#{object_file}") == false
            errors = true
        end

        object_files << "bin/obj/#{object_file}"
    end

    asm_files.each do |file|
        object_file = file.sub(/\.asm$/, '.o')
        object_file = File.basename(object_file)

        if system("#{asm} #{asm_flags} -o bin/obj/#{object_file} #{file} ") == false
            errors = true
        end
        
        object_files << "bin/obj/#{object_file}"
    end

    if errors == true
        puts 'Errors during compilation - halting'
        exit(1)
    else
        system("#{ld} #{ld_flags} -o bin/kernel.bin #{object_files}")

        if build_disk_image == true
            system("cp bin/kernel.bin ./build/iso/boot/kernel.bin")
            system("grub2-mkrescue -o bin/mirus.iso build/iso")
        end
    end
end

task :clean do
    system("rm -rf bin 2>&1")
    system("rm -f *.bin 2>&1")
    system("rm -f *.o 2>&1")
    system("rm -f build/iso/boot/kernel.bin")

    dep_files = cpp_files.sub(/\.cpp$/, '.d')
    system("rm -f #{dep_files} 2>&1")
end

task :qemu do
    system("qemu-system-i386 -cdrom bin/mirus.iso -m 1024m")
end

task :travis do
    build_disk_image = false
    Rake::Task["default"].execute
end