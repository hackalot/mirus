// Copyright (c) 2013 Joshua Beitler, Mirus contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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

    mirus::terminal_initialize();

    // CPU funcs
    mirus::gdt::install();
    mirus::idt::install();
    mirus::isr::install();
    mirus::irq::install();

    // enable interrupts
    asm volatile("sti");

    // try to get avalible memory
    if (mbd->flags & 1)
    {
#ifdef _DEBUG_ON
        mirus::debugger::write("Memory map avalible\n");
#endif
    }
    else
    {
#ifdef _DEBUG_ON
        mirus::debugger::write("No memory map avalible\n");
#endif
    }

    // Install devices
    mirus::keyboard_install();
    mirus::timer_install();
    mirus::serial_install();

    mirus::printf("Mirus\r");

    // Make sure we never exit
    while (true);
}
