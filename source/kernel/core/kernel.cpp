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
// kernel.cpp - main source file + kernel entry point
//

#include <kernel/kernel.h>
#include <kernel/multiboot.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <kernel/tss.h>
#include <kernel/screen.h>
#include <kernel/syscall.h>
#include <kernel/task.h>
#include <kernel/mm.h>
#include <lib/stdio.h>

extern "C" void test_func();

namespace mirus
{
    //
    // Total system memory (in megabytes)
    //
    uint32_t memory_size = 0;

    //
    // Returns memory size in megabytes
    //
    void get_memory_size(multiboot_info_t* mbd)
    {
        memory_map_t* mmap = nullptr;

        if (mbd->flags & 1)
        {
            // Read header and assign
            mmap = (memory_map_t*)mbd->mmap_addr;

            // Parse entries
            while ((unsigned int)mmap < (unsigned int)(mbd->mmap_addr) 
                + mbd->mmap_length)
            {
                memory_size += mmap->length_low;
                mmap = (memory_map_t*)((unsigned int)mmap + mmap->size
                    + sizeof(unsigned int));
            }

            // Get memory size in megabytes
            memory_size = ((memory_size / 1024) / 1024);
        }
    }

    //
    // kernel_main - kernel entry point
    //
    extern "C" void kernel_main(multiboot_info_t* mbd, unsigned int magic)
    {
        get_memory_size(mbd);
        extern char end[];

        Screen::init();
        
        kprintf("mirus firefly [%d.%d.%d-dev]\n\n", __VERSION_MAJOR__, 
            __VERSION_MINOR__, __VERSION_REV__);

        // Initialize hardware
        gdt::init();
        idt::init();
        isr::init();

        init_paging(memory_size, (unsigned int)&end);
        kprintf("[sweet]");

        irq::init();

        // Enable interrupts
        asm volatile("sti");

        init_syscalls();
        enter_userspace();

        // kprintf("kernel addr [%x:%x]\n", 0xFFFFFF, &end);
        // kprintf("kernel size: %dKiB\n\n", ((uint32_t)&end - 0xFFFFFF) / 1024);
        // kprintf("trying paging...");

        // This is the magical system call test function that you've all heard
        // so much about.
        // test_func();

        while (true);
    }
} // !namespace
