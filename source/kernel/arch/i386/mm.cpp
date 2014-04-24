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
#include <kernel/memory.h>
#include <kernel/irq.h>
#include <kernel/regs.h>
#include <lib/stdio.h>

namespace mirus
{
    uint32_t* page_directory = (uint32_t*)PAGE_DIRECTORY_VIRTUAL_ADDRESS;
    uint32_t* page_tables    = (uint32_t*)PAGE_TABLE_VIRTUAL_ADDRESS;

    page_directory_t* current_directory;
    uint32_t location = 0x50000000;

    uint32_t alloc_page()
    {
        uint32_t l = location;
        location = (uint32_t)location + 0x1000;
        return l;
    }

    void free_page()
    {

    }

    void page_fault(regs* r)
    {
        kprintf("page fault\n");
    }

    void init_paging(uint32_t memory_size, unsigned int end)
    {
        /*
            It's simple!

            Copy the location of your page directory into the CR3 register.
            Set the PG bit in the CR0 register. (OR-ing with 0x80000000.)
        */

        uint32_t cr0;

        irq::install_handler(14, &page_fault);

        page_directory_t* page_dir = (page_directory_t*)alloc_page();
        memset(page_dir, 0, 0x1000);

        page_dir[0] = alloc_page() | PAGE_PRESENT | PAGE_WRITE;
        uint32_t* page_table = (uint32_t*) (page_dir[0] & PAGE_MASK);

        for (int i = 0; i < 1024; i++)
        {
            page_table[i] = i * 0x1000 | PAGE_PRESENT | PAGE_WRITE;
        }

        page_dir[1022] = alloc_page() | PAGE_PRESENT | PAGE_WRITE;
        page_table = (uint32_t*)(page_dir[1022] & PAGE_MASK);
        memset(page_table, 0, 0x1000);

        page_table[1023] = (uint32_t)page_dir | PAGE_PRESENT | PAGE_WRITE;
        page_dir[1023] = (uint32_t)page_dir | PAGE_PRESENT | PAGE_WRITE;

        switch_page_directory(page_dir);

        asm volatile("mov %%cr0, %0" : "=r" (cr0));
        cr0 |= 0x80000000;
        asm volatile("mov %0, %%cr0" : : "r" (cr0));    // Triple fault here
    }

    void switch_page_directory(page_directory_t* dir)
    {
        current_directory = dir;
        asm volatile("mov %0, %%cr3" : : "r" (dir));
    }
} // !namespace