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

# define various targets
$target             = "mirus"
$target_iso         = "mirus.iso"
$target_bin         = "kernel.bin"

# build information to be passed to kernel
$version_major      = 0
$version_minor      = 3
$version_rev        = 5
$version_prefix     = "dev"
$version_codename   = "wake"

# source files
$cpp_files          = FileList['source/kernel/**/*.cpp', 'source/system/**/*.cpp', 'source/*.cpp']
$header_files       = FileList['source/include/*.hpp', 'source/common/**/*.h*']
$asm_files          = FileList['source/asm/*.asm']

# object files
$object_files       = $cpp_files.sub(/\.cpp$/, '.o')
$object_files       = $object_files << $asm_files.sub(/\.asm$/, '.o')

# .d files generated by clang
$dep_files          = $cpp_files.sub(/\.cpp$/, '.d')

# clang + additional options
$compiler           = "clang++"
$warnings           = "-Wall -Wextra -Wno-unused-parameter "
$options            = "-fno-builtin -fno-exceptions -ffreestanding -std=c++11 -nostdlib -m32 -O0 "
$include_paths      = "-Isource/include -Isource/library "
$cpp_flags          = $warnings << $options << $include_paths 

$cpp_flags          << "-DBUILD_MAJOR=#{$version_major} "
$cpp_flags          << "-DBUILD_MINOR=#{$version_minor} "
$cpp_flags          << "-DBUILD_REV=#{$version_rev} "
$cpp_flags          << "-DBUILD_PREFIX=#{$version_prefix} "
$cpp_flags          << "-DBUILD_CODENAME=#{$version_codename}"

# asm + options
$assembler          = "yasm"
$assembler_flags    = "-f elf"

# linker options
$ld                 = "ld"
$ld_flags           = "-T build/linker.ld -m elf_i386"

# virtual machine options
$vm                 = "qemu-system-i386"
$vm_flags           = "-serial file:/tmp/mirus_debug.log -cdrom build/mirus.iso -m 1024 -s"

# did we generate any errors?
$errors             = false

# stfu rake
verbose false
