// Copyright 2013 Mirus Project

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// ramdisk.cpp - Tar ramdisk loader
//

#include <stdafx.hpp>
#include <boot/ramdisk.hpp>
#include <system/process/elf.hpp>
#include <system/process/process.hpp>

namespace mirus
{
    namespace boot
    {
        //
        // headers - Headers for all our files
        //
        tar_header_t* headers[32];

        //
        // current_process
        // TODO: move
        //
        system::process_t* current_process;

        //
        // get_size - Get size of tar file
        //
        uint32_t get_size(const char* in)
        {
            uint32_t size = 0;
            uint32_t j;
            uint32_t count = 1;

            for (j = 11; j > 0; j--, count *= 8)
                size += ((in[j - 1] - '0') * count);

            return size;
        }

        //
        // parse_tar - Parse a tar file
        //
        void parse_tar(uint32_t address)
        {
            using namespace system;

            for (uint32_t i = 0; ; i++)
            {
                tar_header_t* header = (tar_header_t*)address;
                char* file_content = (((char*)address) + 512);

                if (header->filename[0] == '\0')
                    break;

                uint32_t size = get_size(header->size);
                headers[i] = header;

                ktrace(trace_level::msg, "Filename: %s\n", header->filename);
                ktrace(trace_level::msg, "\tFile size: %db\n", size);
                ktrace(trace_level::msg, "\tFile content: %s\n", file_content);

                // PARSE ELF ---------------------------------------------------
                // TODO: move

                uint32_t elf_base_addr = (address + 512);
                Elf32_Header* ehdr = (Elf32_Header*)elf_base_addr;

                // Check magic
                if (ehdr->e_ident[0] == ELFMAG0 &&
                    ehdr->e_ident[1] == ELFMAG1 &&
                    ehdr->e_ident[2] == ELFMAG2 &&
                    ehdr->e_ident[3] == ELFMAG3)
                {
                    ktrace(trace_level::msg, "\t\tELF magic matches\n");
                    ktrace(trace_level::msg, "\t\tELF header size: %d\n", ehdr->e_ehsize);
                    ktrace(trace_level::msg, "\t\tELF phdr count: %d\n", ehdr->e_phnum);
                    ktrace(trace_level::msg, "\t\tELF shdr count: %d\n", ehdr->e_shnum);

                    if (ehdr->e_type != ET_EXEC)
                        ktrace(trace_level::error, "\t\tFile not an executable\n");

                    ktrace(trace_level::msg, "\t\tELF entry point: %x\n", ehdr->e_entry);

                    for (uintptr_t x = 0;
                        x < (uint32_t)ehdr->e_shentsize * ehdr->e_shnum;
                        x += ehdr->e_shentsize)
                    {
                        
                    }
                }

                // END ELF -----------------------------------------------------

                address += ((size / 512) + 1) * 512;

                if (size % 512)
                    address += 512;
            }
        }
    } // !namespace
} // !namespace
