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

#include <hw/pit.hpp>
#include <misc/printf.hpp>

unsigned long timer_ticks = 0;
unsigned char timer_subticks = 0;

void mirus::timer_phase(int hz)
{
    int divisor = PIT_SCALE / hz;

    mirus::outb(PIT_CONTROL, PIT_SET);
    mirus::outb(PIT_A, divisor & PIT_MASK);
    mirus::outb(PIT_A, (divisor >> 8) & PIT_MASK);
}

void mirus::timer_handler(struct regs *r)
{
    if (++timer_subticks == SUBTICKS_PER_TICK)
    {
        timer_ticks++;
        timer_subticks = 0;
    }

    mirus::irq::ack(TIMER_IRQ);
}

void mirus::relative_time(unsigned long seconds, unsigned long subseconds, unsigned long *out_seconds, unsigned long *out_subseconds)
{
    if (subseconds + timer_subticks > SUBTICKS_PER_TICK)
    {
        *out_seconds = timer_ticks + seconds + 1;
        *out_subseconds = (subseconds + timer_subticks) - SUBTICKS_PER_TICK;
    }
    else
    {
        *out_seconds = timer_ticks + seconds;
        *out_subseconds = timer_subticks + subseconds;
    }
}

void mirus::timer_install()
{
    mirus::irq::install_handler(TIMER_IRQ, timer_handler);
    mirus::timer_phase(100);
}

void mirus::timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while (timer_ticks < eticks);
}
