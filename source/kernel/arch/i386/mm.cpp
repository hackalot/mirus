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
// mm.cpp - memory manager
//

#include <kernel/mm.h>

namespace mirus
{
    // TODO: Simple code copied from wiki; massively upgrade later on
    void init_paging(uint32_t memory_size, unsigned int end)
    {
        unsigned int kernel_end_page = (((unsigned int)end) & 0xFFFFF000) + 0x1000;
        unsigned int* page_directory = (unsigned int*)kernel_end_page;
        unsigned int* page_table = page_directory + 1024;

        uint32_t frame_count = memory_size / 4;

        // empty all page directory entries
        for (int i = 0; i < 1024; i++)
        {
            page_directory[i] = 0 | 2;
        }

        // little bobby page tables
        unsigned int address = 0;
        for (unsigned int i; i < 1024; i++)
        {
            page_table[i] = address | 3;
            address += 4096;
        }

        // put table in directory
        page_directory[0] = *page_table;
        page_directory[0] |= 3;

        // enable paging
        // ERROR: GPF here.
        asm volatile("mov %0, %%cr3" :: "b"(page_directory));
        unsigned int cr0;
        asm volatile("mov %%cr0, %0": "=b"(cr0));
        cr0 |= 0x80000000;
        asm volatile("mov %0, %%cr0":: "b"(cr0));
    }
} // !namespace