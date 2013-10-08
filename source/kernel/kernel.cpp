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

#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/isr.hpp>
#include <cpu/irq.hpp>

#include <process/process.hpp>

#include <hardware/timer.hpp>
#include <hardware/serial.hpp>
#include <hardware/rtc.hpp>

namespace mirus
{
    // Memory size
    uint32_t memory_size = 0;

    // Memory size (mb)
    uint32_t memory_size_m = 0;

    // Memory map
    memory_map_t* mmap = nullptr;

    // Module count
    uint32_t mod_count = 0;

    // Modules
    module_t* mods = nullptr;

    // Kernel process id
    system::pid_t kernel_pid = 0;

    //
    // kernel_main - our kernel entry point
    //
    extern "C" void kernel_main(multiboot_info_t* mbd, unsigned int magic)
    {
        // Print debug stub
        ktrace(trace_level::log, "Mirus 0.2.5-dev\n\n");

        // Get avalible memory
        if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
            ktrace(trace_level::error, 
                "Multiboot bootloader magic doesn't match!\n");

        mod_count = mbd->mods_count;

        if (mbd->flags & 1)
        {
            ktrace(trace_level::log, "Reading multiboot header\n");
            mmap = (memory_map_t*)mbd->mmap_addr;

            // parse entries
            while ((unsigned int)mmap < (unsigned int)(mbd->mmap_addr) + mbd->mmap_length)
            {
                memory_size += mmap->length_low;
                mmap = (memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
            }

            memory_size_m = ((memory_size / 1024) / 1024);

            ktrace(trace_level::log, 
                "Avalible memory: %dm\n", 
                memory_size_m);
            ktrace(trace_level::log, 
                "Trying to get ramdisk.\n");

            // Check for any modules, the only of which should be the ramdisk
            if (mod_count > 0)
            {
                ktrace(trace_level::log, 
                    "Modules found: %d\n", 
                    mod_count);

                uint32_t i = 0;
                for (i = 0, mods = (module_t*)mbd->mods_addr;
                    i < mod_count;
                    i++, mods++)
                {

                }
            }
            else
            {
                ktrace(trace_level::log, "No modules found.\n");
            }
        }

        if (memory_size_m < 512)
            ktrace(trace_level::warning, 
                "Memory is less than expected minimum\n");

        // Install GDT
        ktrace(trace_level::log, "Installing GDT...");
        cpu::gdt::install();
        ktrace(trace_level::none, "OK\n");

        // Install IDT
        ktrace(trace_level::log, "Installing IDT...");
        cpu::idt::install();
        ktrace(trace_level::none, "OK\n");

        // Setup ISRs
        ktrace(trace_level::log, "Setting up ISRs...");
        cpu::isr::install();
        ktrace(trace_level::none, "OK\n");

        // Setup IRQs
        ktrace(trace_level::log, "Setting up IRQs...");
        cpu::irq::install();
        ktrace(trace_level::none, "OK\n");

        // Setup screen
        ktrace(trace_level::log, "Setting up screen...");
        screen::terminal::install();
        ktrace(trace_level::none, "OK\n");

        // Setup timer
        ktrace(trace_level::log, "Setting up timer...");
        hardware::pit::install();
        ktrace(trace_level::none, "OK\n");

        // Setup serial ports
        ktrace(trace_level::log, "Setting up serial ports...");
        hardware::serial::install();
        ktrace(trace_level::none, "OK\n");

        // WE MUST NEVER RETURN!!!!
        while (true);
    }
} // !namespace
