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

#include <hardware/timer.hpp>
#include <hardware/serial.hpp>
#include <hardware/rtc.hpp>

#include <msg/message_handler.hpp>
#include <msg/message.hpp>

#include <util/printf.hpp>

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

    //
    // kernel_main - our kernel entry point
    //
    extern "C" void kernel_main(multiboot_info_t* mbd, unsigned int magic)
    {
        // Print debug stub
        debug::debugger::write("[log] Mirus 0.2.5-dev\n\n");

        // Get avalible memory
        if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
            debug::debugger::write("[error] Multiboot bootloader magic doesn't match!\n");

        mod_count = mbd->mods_count;

        if (mbd->flags & 1)
        {
            debug::debugger::write("[log] Reading multiboot header\n");
            mmap = (memory_map_t*)mbd->mmap_addr;

            // parse entries
            while ((unsigned int)mmap < (unsigned int)(mbd->mmap_addr) + mbd->mmap_length)
            {
                memory_size += mmap->length_low;
                mmap = (memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
            }

            memory_size_m = ((memory_size / 1024) / 1024);

            debug::debugger::write("[log] Avalible memory: %dm\n", memory_size_m);
            debug::debugger::write("[log] Trying to get ramdisk.\n");

            // Check for any modules, the only of which should be the ramdisk
            if (mod_count > 0)
            {
                debug::debugger::write("[log] Modules found: %d\n", mod_count);

                uint32_t i = 0;
                for (i = 0, mods = (module_t*)mbd->mods_addr;
                    i < mod_count;
                    i++, mods++)
                {

                }
            }
            else
            {
                debug::debugger::write("[log] No modules found.\n");
            }
        }

        if (memory_size_m < 512)
            debug::debugger::write("[warning] Memory is less than expected minimum\n");

        // Install GDT
        debug::debugger::write("[log] Installing GDT...");
        cpu::gdt::install();
        debug::debugger::write("OK\n");

        // Install IDT
        debug::debugger::write("[log] Installing IDT...");
        cpu::idt::install();
        debug::debugger::write("OK\n");

        // Setup ISRs
        debug::debugger::write("[log] Setting up ISRs...");
        cpu::isr::install();
        debug::debugger::write("OK\n");

        // Setup IRQs
        debug::debugger::write("[log] Setting up IRQs...");
        cpu::irq::install();
        debug::debugger::write("OK\n");

        // Setup screen
        debug::debugger::write("[log] Setting up screen...");
        screen::terminal::install();
        debug::debugger::write("OK\n");

        // Setup timer
        debug::debugger::write("[log] Setting up timer...");
        hardware::pit::install();
        debug::debugger::write("OK\n");

        // Setup serial ports
        debug::debugger::write("[log] Setting up serial ports...");
        hardware::serial::install();
        debug::debugger::write("OK\n");

        kprintf("hello");

        // WE MUST NEVER RETURN!!!!
        while (true);
    }
} // !namespace
