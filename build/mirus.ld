OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

phys = 0xFFFFFF;

SECTIONS
{
    .text phys : AT(phys) {
        code = .;
        *(.multiboot*)
        *(.text*)
        *(.rodata*)
        . = ALIGN(4096);
    }

    .data : AT(phys + (data - code))
    {
        data = .;
        *(.data*)
        PROVIDE(kernel_symbols_start = .);
        PROVIDE(kernel_symbols_end = .);
        . = ALIGN(4096);
    }

    .bss : AT(phys + (bss - code))
    {
        bss = .;
        *(.bss*)
        . = ALIGN(4096);
    }

    end = .;

    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
        *(.note.gnu.build-id)
    }
}