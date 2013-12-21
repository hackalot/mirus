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
// paging.cpp - interface for paging and related structures
//

#include <mem/paging.hpp>
#include <mem/kheap.hpp>

namespace mirus
{
    namespace mem
    {
        page_directory_t* kernel_directory = 0;
        page_directory_t* current_directory = 0;

        uint32_t* frames;
        uint32_t nframes;

        extern uint32_t placement_address;

        #define INDEX_FROM_BIT(a) (a / 0x20)
        #define OFFSET_FROM_BIT(a) (a % 0x20)

        static void set_frame(uint32_t frame_addr)
        {
            uint32_t frame = frame_addr / 0x1000;
            uint32_t index = INDEX_FROM_BIT(frame);
            uint32_t offset = OFFSET_FROM_BIT(frame);
            
            frames[index] |= (0x1 << offset);
        }

        static void clear_frame(uint32_t frame_addr)
        {
            uint32_t frame = frame_addr / 0x1000;
            uint32_t index = INDEX_FROM_BIT(frame);
            uint32_t offset = OFFSET_FROM_BIT(frame);
            
            frames[index] &= ~(0x1 << offset);
        }

        static uint32_t test_frame(uint32_t frame_addr)
        {
            uint32_t frame = frame_addr / 0x1000;
            uint32_t index = INDEX_FROM_BIT(frame);
            uint32_t offset = OFFSET_FROM_BIT(frame);

            return (frames[index] & (0x1 << offset));
        }

        static uint32_t first_frame()
        {
            for (uint32_t i = 0; i < INDEX_FROM_BIT(nframes); i++)
            {
                if (frames[i] != 0xFFFFFFFF)
                {
                    for (uint32_t j = 0; j < 32; j++)
                    {
                        uint32_t test = 0x1 << j;

                        if (!(frames[i]&test))
                            return i*4*8+j;
                    }
                }
            }
        }

        void alloc_frame(page_t* page, uint32_t is_kernel, int is_writeable)
        {
            if (page->frame != 0)
            {
                page->present = 1;
                page->rw = (is_writeable == 1) ? 1:0;
                page->user = (is_kernel == 1) ? 0:1;
                return;
            }
            else
            {
                uint32_t index = first_frame();
                set_frame(index * 0x1000);
                page->present = 1;
                page->rw = (is_writeable == 1) ? 1:0;
                page->user = (is_kernel == 1) ? 0:1;
                page->frame = index;
            }
        }

        void free_frame(page_t* page)
        {
            uint32_t frame;

            if (!(frame = page->frame))
                return;
            else
            {
                clear_frame(frame * 0x1000);
                page->frame = 0x0;
            }
        }

        void paging::init(uint32_t memsize)
        {
            // uint32_t mem_end_page = 0x1000000;
            // nframes = mem_end_page / 0x1000;
            nframes = memsize / 4;
            frames = (uint32_t*)kmalloc(INDEX_FROM_BIT(nframes * 8));
            memset(frames, 0, INDEX_FROM_BIT(nframes));

            kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
            current_directory = kernel_directory;

            for (uintptr_t i = 0; i < placement_address + 0x3000; i += 0x1000) 
            {
                alloc_frame(get_page(i, 1, kernel_directory), 1, 0);
            }

            cpu::irq::install_handler(14, paging::page_fault);
            kernel_directory->physical_address = (uintptr_t)kernel_directory->tables_physical;
            paging::switch_page_directory(kernel_directory);
        }

        void paging::switch_page_directory(page_directory_t* dir)
        {
            current_directory = dir;

            asm volatile("mov %0, %%cr3":: "r"(current_directory->physical_address));
            uint32_t cr0;
            asm volatile("mov %%cr0, %0": "=r"(cr0));
            cr0 |= 0x80000000;
            asm volatile("mov %0, %%cr0":: "r"(cr0));
        }

        page_t* paging::get_page(uint32_t address, int make, page_directory_t* dir)
        {
            address /= 0x1000;
            uint32_t table_index = address / 1024;

            if (dir->tables[table_index])
                return &dir->tables[table_index]->pages[address % 1014];
            else if (make)
            {
                uint32_t temp;
                
                dir->tables[table_index] = 
                    (page_table_t*)kmalloc_ap(sizeof(page_table_t), &temp);
                dir->tables_physical[table_index] = temp | 0x7;
                return &dir->tables[table_index]->pages[address % 1014];
            }
            else
                return 0;
        }

        void paging::page_fault(cpu::regs* regs)
        {
            // A page fault has occurred.
            // The faulting address is stored in the CR2 register.
            uint32_t faulting_address;
            asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
            
            // The error code gives us details of what happened.
            int present   = !(regs->err_code & 0x1); // Page not present
            int rw = regs->err_code & 0x2;           // Write operation?
            int us = regs->err_code & 0x4;           // Processor was in user-mode?
            int reserved = regs->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
            int id = regs->err_code & 0x10;          // Caused by an instruction fetch?

            // Output an error message.
            kprintf("Page fault! ( ");
            if (present) {kprintf("present ");}
            if (rw) {kprintf("read-only ");}
            if (us) {kprintf("user-mode ");}
            if (reserved) {kprintf("reserved ");}
            kprintf(") at %x\n", faulting_address);
        }
    } // !namespace
} // !namespace