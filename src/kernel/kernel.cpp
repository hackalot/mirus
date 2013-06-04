#include <term/terminal.hpp>
#include <misc/printf.hpp>
#include <cpu/gdt.hpp>

extern "C" void kernel_main()
{
	mirus::gdt_install();
	terminal_initialize();

	mirus::printf("mirus ");
	mirus::printf(BUILD_MAJOR);
	mirus::printf(".");
	mirus::printf(BUILD_MINOR);
	mirus::printf(".");
	mirus::printf(BUILD_NUM);
}
