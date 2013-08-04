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

#ifndef _MIRUS_KERNEL_BRAD_PIT_H_  // haha...
#define _MIRUS_KERNEL_BRAD_PIT_H_

#include <cpu/register.hpp>
#include <cpu/irq.hpp>
#include <core/ioport.hpp>

#define PIT_A 0x40
#define PIT_B 0x41
#define PIT_C 0x42
#define PIT_CONTROL 0x43

#define PIT_MASK 0xFC
#define PIT_SCALE 1193180
#define PIT_SET 0x36

#define TIMER_IRQ 0

#define SUBTICKS_PER_TICK 100

// TODO: move under a hw::pit class

namespace mirus
{
    // set timer freq.
    void timer_phase(int hz);
    
    // handler the timer
    void timer_handler(struct regs *r);
    
    void relative_time(unsigned long seconds, unsigned long subseconds, unsigned long *out_seconds, unsigned long *out_subseconds);
   
    // install the timer
    void timer_install();
    
    // wait 'n' seconds
    void timer_wait(int ticks);
}

#endif
