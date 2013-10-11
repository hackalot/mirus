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
// multiboot.hpp - Multiboot implimentation
//

#pragma once

#include <stdafx.hpp>

namespace mirus
{
    //
    // Multiboot magic number
    //
    const uint32_t HEADER_MAGIC = 0x1BADB002;

    //
    // Flags
    //
    #ifdef __ELF__
        const uint32_t HEADER_FLAGS = 0x00000003;
    #else
        const uint32_t HEADER_FLAGS = 0x00010003;
    #endif

    //
    // Bootlaoder magic
    //
    const uint32_t BOOTLOADER_MAGIC = 0x2BADB002;

    //
    // Stack size
    //
    const uin32_t STACK_SIZE = 0x4000;

    //
    // Multiboot header
    //
    class multiboot_header_t
    {
    public:
        uint32_t magic;
        uint32_t flags;
        uint32_t checksum;
        uint32_t header_addr;
        uint32_t load_addr;
        uint32_t load_end_addr;
        uint32_t bss_end_addr;
        uint32_t entry_addr;
    };

    //
    // A.out symbol table
    //
    class aout_symbol_table_t
    {
    public:
        uint32_t tabsize;
        uint32_t strsize;
        uint32_t addr;
        uint32_t reserved;
    };

    //
    // Elf section header
    //
    class elf_section_header_t
    {
    public:
        uint32_t num;
        uint32_t size;
        uint32_t addr;
        uint32_t shndx;
    };

    //
    // Multiboot header
    //
    class multiboot_info_t
    {
    
    };
} // !namespace