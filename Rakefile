require 'colorize'

target          = "mirus"
iso_target      = target << ".iso"
bin_target      = target << ".bin"

cpp_files       = FileList['source/kernel/*.cpp', 'source/system/*.cpp']
header_files    = FileList['source/include/*.hpp', 'source/library/*.hpp']
asm_files       = FileList['source/assembly/*.asm']

object_files    = cpp_files.sub(/\.cpp$/, '.o')
object_files    = object_files << asm_files.sub(/\.asm$/, '.o')

dep_files       = cpp_files.sub(/\.cpp$/, '.d')

aux_files       = FileList['support/*']
all_files       = cpp_files << header_files << asm_files << aux_files

compiler        = "clang++"
warnings        = "-Wall -Wextra"
options         = "-fno-builtin -fno-exceptions -ffreestanding -std=c++11 -m32 -O0"
include_paths   = "-I source/include -I source/library"
cpp_flags       = warnings << options << include_paths << "-c -MMD -MP"

assembler       = "nasm"
assembler_flags = "-f elf"

vm              = "qemu-system-i386"
vm_flags        = "-serial file:/tmp/mirus_debug.log"

# create a directory to hold output
directory "build"

# stfu rake
verbose false

# compile
desc "Build all components"
task :build_all => ['build_asm', 'build_kernel'] do
    # ...
end

# build kernel
desc "Build the kernel"
task :build_kernel do
    # ...
end

# build assembly
desc "Build bootstrap + lower level ASM code"
task :build_asm do
    asm_files.each do |t|
        object_file = t.sub(/\.asm$/, '.o')
        
        sh "#{assembler} #{assembler_flags} -o #{object_file} #{t}" do |ok, res|
            if ! ok
                puts "[rake] Could not build #{t}".red
                puts "\t#{res}.exitstatus".red
            else
                puts "[rake] #{t} -> #{object_file}".green
            end
        end
    end
end

# generate a bootable iso image of Mirus
desc "Creates bootable media"
task :make_iso do
    puts "Generating ISO..."
end

# clean object files, etc.
desc "Clean up all the extra crap"
task :clean do
    sh "rm -f #{object_files}"
    sh "rm -f #{dep_files}"
end

# start qemu
desc "Start QEMU with Mirus"
task :qemu do
    sh "#{vm} #{vm_flags} build/mirus.iso"
end

# default task
task :default => ['make_iso']
