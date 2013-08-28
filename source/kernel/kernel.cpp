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

#include <system.hpp>

#include <misc/multiboot.hpp>
#include <term/terminal.hpp>
#include <cpu/cpuid.hpp>

#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/isr.hpp>
#include <cpu/irq.hpp>

#include <hw/pit.hpp>
#include <hw/keyboard.hpp>
#include <hw/serial.hpp>

extern "C" void kernel_main(multiboot_info_t* mbd, unsigned int magic)
{
#ifdef _DEBUG_ON
    mirus::debugger::write("mirus now booting\n\n");
#endif

    // CPU funcs
    mirus::gdt::install();
    mirus::idt::install();
    mirus::isr::install();
    mirus::irq::install();

    // enable interrupts
    asm volatile("sti");

    // check if bootloader is valid
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
#ifdef _DEBUG_ON
        mirus::debugger::write("Multiboot bootloader magic doesn't match!\n");
#endif
    }

    int memory_size = 0;
    // try to get available memory
    if (mbd->flags & 1)
    {
#ifdef _DEBUG_ON
        mirus::debugger::write("Memory map present - try to get available memory\n");
#endif
        memory_map_t * mmap = (memory_map_t *)mbd->mmap_addr;
        // parse each entry
        while ((unsigned int)mmap < (unsigned int)(mbd->mmap_addr) + mbd->mmap_length) {
            memory_size += mmap->length_low;

            mmap = (memory_map_t *)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
        }

#ifdef _DEBUG_ON
        mirus::debugger::write("Available memory: ");
        mirus::debugger::write(memory_size / 1024);
        mirus::debugger::write("k\n");
#endif
    }
    else
    {
#ifdef _DEBUG_ON
        mirus::debugger::write("No memory map available\n");
#endif
    }

    // Install devices
    mirus::io::terminal::initilize();
    mirus::keyboard_install();
    mirus::timer_install();
    mirus::serial_install();

    mirus::printf("Mirus");

    // Make sure we never exit
    while (true);
}
