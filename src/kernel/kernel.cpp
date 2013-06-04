#include <term/terminal.hpp>
#include <misc/printf.hpp>

#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/isr.hpp>

extern "C" void kernel_main()
{
    // install the GDT
	mirus::gdt_install();

    // install the IDT
    mirus::idt_install();

    // install ISRs
    mirus::isrs_install();

    // initilize display
	terminal_initialize();

    // print version number
	mirus::printf("mirus ");
	mirus::printf(BUILD_MAJOR);
	mirus::printf(".");
	mirus::printf(BUILD_MINOR);
	mirus::printf(".");
	mirus::printf(BUILD_NUM);

    // Try to trigger the ISR errors
    int bob[2];
    bob[0] = 33;
    bob[1] = 33;
    bob[2] = 666;
    bob[3] = 666;
}
