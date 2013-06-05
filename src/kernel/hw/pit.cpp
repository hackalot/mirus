#include <hw/pit.hpp>
#include <misc/printf.hpp>

unsigned long timer_ticks = 0;
unsigned char timer_subticks = 0;

void mirus::timer_phase(int hz) {
    int divisor = PIT_SCALE / hz;

    mirus::outb(PIT_CONTROL, PIT_SET);
    mirus::outb(PIT_A, divisor & PIT_MASK);
    mirus::outb(PIT_A, (divisor >> 8) & PIT_MASK);
}

void mirus::timer_handler(struct regs *r) {
    if (++timer_subticks == SUBTICKS_PER_TICK) {
        timer_ticks++;
        timer_subticks = 0;
    }

    mirus::irq_ack(TIMER_IRQ);
}

void mirus::relative_time(unsigned long seconds, unsigned long subseconds, unsigned long * out_seconds, unsigned long * out_subseconds) {
    if (subseconds + timer_subticks > SUBTICKS_PER_TICK) {
        *out_seconds = timer_ticks + seconds + 1;
        *out_subseconds = (subseconds + timer_subticks) - SUBTICKS_PER_TICK;
    } else {
        *out_seconds = timer_ticks + seconds;
        *out_subseconds = timer_subticks + subseconds;
    }
}

void mirus::timer_install() {
    mirus::irq_install_handler(TIMER_IRQ, timer_handler);
    mirus::timer_phase(100);
}

void mirus::timer_wait(int ticks) {
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}
