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

// just a test
typedef struct initrd_hdr
{
    uint32_t magic;
} hdr_t;

namespace mirus
{
    //
    // kernel_main - our kernel entry point
    //
    extern "C" void kernel_main(multiboot_info_t* mbd, 
        unsigned int magic)
    {
        // Print debug stub
        debug::debugger::writeln("[log] Mirus 0.2.5-dev\n");

        uintptr_t ramdisk_top = 0;
        char*     ramdisk;

        // Get avalible memory
        if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
            debug::debugger::writeln("[error] Multiboot bootloader magic doesn't match!");

        int memory_size = 0;

        if (mbd->flags & 1)
        {
            debug::debugger::writeln("[log] Reading multiboot header");

            memory_map_t* mmap = (memory_map_t*)mbd->mmap_addr;

            // parse entries
            while ((unsigned int)mmap < (unsigned int)(mbd->mmap_addr) + mbd->mmap_length)
            {
                memory_size += mmap->length_low;
                mmap = (memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
            }

            debug::debugger::write("[log] Avalible memory: ");
            debug::debugger::write((memory_size / 1024) / 1024);
            debug::debugger::writeln("m");

            debug::debugger::writeln("[log] Trying to get ramdisk.");

            // Check for any modules, the only of which should be the ramdisk
            if (mbd->mods_count > 0)
            {
                debug::debugger::write("[log] Modules found: ");
                debug::debugger::writeln((int)mbd->mods_count);

                uint32_t* module_start = ((uint32_t*)mbd->mods_addr);
                uint32_t* module_end   = ((uint32_t*)(mbd->mods_addr + 4));

                debug::debugger::write("[log] Module start: ");
                debug::debugger::writeln((int)&module_start);

                hdr_t* header = (hdr_t*)*module_start;

                debug::debugger::write("[log] Value: ");
                debug::debugger::writeln((unsigned int)header->magic);
            }
            else
            {
                debug::debugger::writeln("[log] No modules found.");
            }
        }

        if (((memory_size / 1024) / 1024) < 512)
            debug::debugger::writeln("[warning] Memory is less than expected minimum");

        // Install CPU hardware devices
        cpu::gdt::install();
        cpu::idt::install();
        cpu::isr::install();
        cpu::irq::install();

        // Set up screen
        screen::terminal::install();

        // Set up additional hardware
        hardware::pit::install();
        hardware::serial::install();

        // Testing the message system
        system::message_t msg;
        msg.pid_sender = 0;
        msg.pid_dest = 0;
        msg.priority = 0;
        msg.type = (int)system::message_request_type::pingback;
        msg.data = "this is your kernel speaking, enjoy the ride.";

        // message_handler::dispatch_message(msg);

        // WE MUST NEVER RETURN!!!!
        while (true);
    }
} // !namespace
