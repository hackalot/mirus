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
//              we all have to begin somewhere, right?
//
    
#include <stdafx.hpp>
#include <boot/multiboot.hpp>
#include <boot/ramdisk.hpp>

#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/isr.hpp>
#include <cpu/irq.hpp>

#include <system/process/process.hpp>
#include <system/process/elf.hpp>
#include <system/process/task.hpp>

#include <system/syscall.hpp>

#include <hardware/timer.hpp>
#include <hardware/serial.hpp>
#include <hardware/rtc.hpp>

namespace mirus
{
    extern "C" void test_func();

    //
    // Memory size
    //
    uint32_t memory_size = 0;

    //
    // Memory size (mb)
    //
    uint32_t memory_size_m = 0;

    //
    // Memory map
    //
    memory_map_t* mmap = nullptr;

    //
    // Module count
    //
    uint32_t mod_count = 0;

    //
    // Modules
    //
    module_t* mods = nullptr;

    //
    // Minimum memory size (512mb)
    //
    uint32_t min_mem = 512;

    //
    // kernel_main - our kernel entry point
    //
    extern "C" void kernel_main(multiboot_info_t* mbd, unsigned int magic)
    {
        // Print debug stub
        ktrace(trace_level::msg, "Mirus 0.3.5-dev\n\n");

        // Get avalible memory
        if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
            ktrace(trace_level::error, 
                "Multiboot bootloader magic doesn't match!\n");

        // Retrieve number of multiboot modules
        mod_count = mbd->mods_count;

        // Verify if multiboot flags are ok to go
        if (mbd->flags & 1)
        {
            // Read header and assign
            ktrace(trace_level::msg, "Reading multiboot header\n");
            mmap = (memory_map_t*)mbd->mmap_addr;

            // Parse entries
            while ((unsigned int)mmap < (unsigned int)(mbd->mmap_addr) + mbd->mmap_length)
            {
                memory_size += mmap->length_low;
                mmap = (memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
            }

            // Get memory size in megabytes
            memory_size_m = ((memory_size / 1024) / 1024);

            ktrace(trace_level::msg, 
                "Avalible memory: %dm\n", 
                memory_size_m);
        }

        // Check for any modules, the only of which should be the ramdisk
        ktrace(trace_level::msg, "Trying to get ramdisk...\n");

        if (mod_count > 0)
        {
            kprintf("Loading ramdisk...");

            ktrace(trace_level::msg, 
                "Modules found: %d\n", 
                mod_count);

            uint32_t i = 0;
            for (i = 0, mods = (module_t*)mbd->mods_addr;
                i < mod_count;
                i++, mods++)
            {
                ktrace(trace_level::none, "==========\n");
                ktrace(trace_level::msg, "Module found: [%d:%d]\n",
                    mods->mod_start,
                    mods->mod_end);

                // load the ramdisk
                boot::parse_tar(mods->mod_start);
                kprintf("[ OK ]\n");

                ktrace(trace_level::none, "==========\n");
            }
        }
        else
        {
            ktrace(trace_level::msg, "No modules found.\n");
            kprintf("[ERROR]\n");
        }

        // Check for minimum memory size
        if (memory_size_m < min_mem)
            ktrace(trace_level::warn, 
                "Memory is less than expected minimum\n");

        // Install GDT
        ktrace(trace_level::msg, "Installing GDT...");
        cpu::gdt::install();
        ktrace(trace_level::none, "OK\n");

        // Install IDT
        ktrace(trace_level::msg, "Installing IDT...");
        cpu::idt::install();
        ktrace(trace_level::none, "OK\n");

        // Setup ISRs
        ktrace(trace_level::msg, "Setting up ISRs...");
        cpu::isr::install();
        ktrace(trace_level::none, "OK\n");

        // Setup screen
        ktrace(trace_level::msg, "Setting up screen...");
        screen::terminal::install();
        ktrace(trace_level::none, "OK\n");

        // Setup serial ports
        ktrace(trace_level::msg, "Setting up serial ports...");
        hardware::serial::install();
        ktrace(trace_level::none, "OK\n");

        // Setup IRQs
        ktrace(trace_level::msg, "Setting up IRQs...");
        cpu::irq::install();
        ktrace(trace_level::none, "OK\n");

        // Print kernel information
        kprintf("Mirus [%d.%d.%d-dev]\n\n", BUILD_MAJOR, BUILD_MINOR, BUILD_REV);
        kprintf("Unless required by applicable law or agreed to in writing, software\n");
        kprintf("distributed under the License is distributed on an \"AS IS\" BASIS,\n");
        kprintf("WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
        kprintf("limitations under the License.\n\n");

        // Set up system calls
        ktrace(trace_level::msg, "Installing system calls...");
        system::init_syscalls();
        ktrace(trace_level::none, "OK\n");

        // Enter usermode
        ktrace(trace_level::notice, "Entering usermode...");
        system::enter_userspace();
        ktrace(trace_level::none, "OK\n");

        // ERROR: causes gpf when either of these happen
        //        possibly (but not likely) a bug in the 
        //        ISR or IRQ code
        //
        //        * test_func();
        //        * asm volatile("mov $0x0, %eax\n"
        //          "int $0x80");

        asm volatile("mov $0x0, %eax");
        asm volatile("mov $0x0, %ebx");
        asm volatile("mov $0x0, %ecx");
        asm volatile("mov $0x0, %edx");
        asm volatile("mov $0x0, %esi");
        asm volatile("mov $0x0, %edi");
        asm volatile("int $0x7F");

        // system::test_syscalls(0);

        // The point of no return (heh...)
        while (true);
    }
} // !namespace
