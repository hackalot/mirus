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

arch = 'i386'
arch_c = '__ARCH_I386__'
target = 'mirus'

cxx = 'clang++'
ld  = 'ld'
asm = 'yasm'

cxx_flags = '-fno-builtin -fno-exceptions -ffreestanding -std=c++11 -m32 -Isource/include '
cxx_flags << "-D#{arch_c}"
asm_flags = '-f elf'
ld_flags = '-T build/mirus.ld -m elf_i386'

cpp_files = FileList[
    "source/kernel/core/**/*.cpp", 
    "source/kernel/arch/#{arch}/**/*.cpp"]

asm_files = FileList[
    "source/kernel/core/**/*.asm",
    "source/kernel/arch/#{arch}/**/*.asm"]

object_files = FileList[]

task :default do
    system('mkdir bin bin/obj 2>&1')

    cpp_files.each do |file|
        object_file = file.sub(/\.cpp$/, '.o')
        object_file = File.basename(object_file)
        system("#{cxx} #{cxx_flags} -MMD -MP -c #{file} -o bin/obj/#{object_file}")
        object_files << "bin/obj/#{object_file}"
    end

    asm_files.each do |file|
        object_file = file.sub(/\.asm$/, '.o')
        object_file = File.basename(object_file)
        system("#{asm} #{asm_flags} -o bin/obj/#{object_file} #{file} ")
        object_files << "bin/obj/#{object_file}"
    end

    system("#{ld} #{ld_flags} -o bin/kernel.bin #{object_files}")
    system("cp bin/kernel.bin ./build/iso/boot/kernel.bin")
    system("grub2-mkrescue -o bin/mirus.iso build/iso")
end

task :clean do
    system("rm -rf bin 2>&1")
    system("rm -f *.bin 2>&1")
    system("rm -f *.o 2>&1")
    system("rm -f *.d 2>&1")
    system("rm -f build/iso/boot/kernel.bin")
end

task :qemu do
    system("qemu-system-i386 -cdrom bin/mirus.iso")
end