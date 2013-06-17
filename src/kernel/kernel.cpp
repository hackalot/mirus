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

#include <term/terminal.hpp>
#include <misc/printf.hpp>

#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/isr.hpp>
#include <cpu/irq.hpp>

#include <hw/pit.hpp>
#include <hw/keyboard.hpp>

extern "C" void kernel_main()
{
    // install the GDT
	mirus::gdt_install();

    // install the IDT
    mirus::idt_install();

    // install ISRs
    mirus::isrs_install();

    // install IRQs
    mirus::irq_install();

    // initilize display
	mirus::terminal_initialize();

    // install keyboard
    mirus::keyboard_install();

    // install timer
    mirus::timer_install();

    asm volatile("sti");

    // print version number
	mirus::printf("mirus ");
	mirus::printf(BUILD_MAJOR);
	mirus::printf(".");
	mirus::printf(BUILD_MINOR);
	mirus::printf(".");
	mirus::printf(BUILD_NUM);
    mirus::printf("\r");
    mirus::printf("\r");

    mirus::printf("> ");

    // Make sure we never exit
    while (true);
}
