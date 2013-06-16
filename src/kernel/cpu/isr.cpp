#include <cpu/isr.hpp>

extern "C" {
    void isr0();
    void isr1();
    void isr2();
    void isr3();
    void isr4();
    void isr5();
    void isr6();
    void isr7();
    void isr8();
    void isr9();
    void isr10();
    void isr11();
    void isr12();
    void isr13();
    void isr14();
    void isr15();
    void isr16();
    void isr17();
    void isr18();
    void isr19();
    void isr20();
    void isr21();
    void isr22();
    void isr23();
    void isr24();
    void isr25();
    void isr26();
    void isr27();
    void isr28();
    void isr29();
    void isr30();
    void isr31();
}

void mirus::isrs_install() {
    using namespace mirus;

    idt_set_gate(0, (unsigned long)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned long)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned long)isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned long)isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned long)isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned long)isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned long)isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned long)isr7, 0x08, 0x8E);

    idt_set_gate(8, (unsigned long)isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned long)isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned long)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned long)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned long)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned long)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned long)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned long)isr15, 0x08, 0x8E);

    idt_set_gate(16, (unsigned long)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned long)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned long)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned long)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned long)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned long)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned long)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned long)isr23, 0x08, 0x8E);

    idt_set_gate(24, (unsigned long)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned long)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned long)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned long)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned long)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned long)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned long)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned long)isr31, 0x08, 0x8E);
}

const char* exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void mirus::fault_handler(struct regs* r) {
    if (r->int_no < 32) {
        printf(exception_messages[r->int_no]);
        printf(" Exception. System Halted!\r");
        for (;;);
    }
}