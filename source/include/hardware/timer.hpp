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

//
// timer.hpp - PIT implimentation
//

#pragma once

#include <stdafx.hpp>
#include <cpu/regs.hpp>

namespace mirus
{
    namespace hardware
    {
        const int PIT_A = 0x40;
        const int BIT_B = 0x41;
        const int PIT_C = 0x42;
        const int PIT_CONTROL = 0x43;

        const int PIT_MASK = 0xFC;
        const int PIT_SCALE = 1193180;
        const int PIT_SET = 0x36;

        const int TIMER_IRQ = 0;
        const int SUBTICKS_PER_TICK = 100;

        class pit
        {
        public:
            static void phase(int hz);
            static void handle_timer(cpu::regs* r);
            static void relative_time(unsigned long seconds, 
                unsigned long subseconds, 
                unsigned long *out_seconds, 
                unsigned long *out_subseconds);
            static void wait(int ticks);

            static void install();
        };
    } // !namespace
} // !namespace