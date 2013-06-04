#include <term/terminal.hpp>
#include <misc/printf.hpp>
#include <cpu/gdt.hpp>

extern "C" void kernel_main()
{
    // install the GDT
	mirus::gdt_install();

    // initilize display
	terminal_initialize();

    // set up system version


	mirus::printf("mirus ");
	mirus::printf(BUILD_MAJOR);
	mirus::printf(".");
	mirus::printf(BUILD_MINOR);
	mirus::printf(".");
	mirus::printf(BUILD_NUM);
}
