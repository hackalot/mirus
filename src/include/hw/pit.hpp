#ifndef _MIRUS_KERNEL_BRAD_PIT_H_  // haha...
#define _MIRUS_KERNEL_BRAD_PIT_H_

#include <cpu/register.hpp>
#include <cpu/irq.hpp>
#include <core/ioport.hpp>

#define PIT_A 0x40
#define PIT_B 0x41
#define PIT_C 0x42
#define PIT_CONTROL 0x43

#define PIT_MASK 0xFE
#define PIT_SCALE 1193180
#define PIT_SET 0x36

#define TIMER_IRQ 0

#define SUBTICKS_PER_TICK 100

namespace mirus {
    void timer_phase(int hz);
    void timer_handler(struct regs* r);
    void relative_time(unsigned long seconds, unsigned long subseconds, unsigned long * out_seconds, unsigned long * out_subseconds);
    void timer_install();
    void timer_wait(int ticks);
}

#endif