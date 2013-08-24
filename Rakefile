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

directory "build"

# compile
desc "Build all components"
task :build_all => ['build_asm', 'build_kernel'] do

end

# build kernel
desc "Build the kernel"
task :build_kernel do

end

# build assembly
desc "Build bootstrap + lower level ASM code"
task :build_asm do
    asm_files.each do |t|
        object_file = t.sub(/\.asm$/, '.o')
        sh "#{assembler} #{assembler_flags} -o #{object_file} #{t}"
    end
end

# generate a bootable iso image of Mirus
desc "Creates bootable media"
task :make_iso do
    puts "Generating ISO..."
end

desc "Clean up all the extra crap"
task :clean do
    sh "rm -f #{object_files}"
    sh "rm -f #{dep_files}"
end

task :default => ['make_iso']