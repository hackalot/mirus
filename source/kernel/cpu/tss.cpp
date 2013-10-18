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
// tss.cpp - Task state segment
//

#include <cpu/tss.hpp>
#include <cpu/gdt.hpp>

namespace mirus
{
    namespace cpu
    {
        tss_entry_t tss_entry;

        void tss::write(int32_t num, uint16_t ss0, uint32_t esp0)
        {
            uint32_t base = (uint32_t)&tss_entry;
            uint32_t limit = base + sizeof(tss_entry);

            gdt::set_gate(num, base, limit, 0xE9, 0x00);

            memset_v(&tss_entry, 0x0, sizeof(tss_entry));

            tss_entry.ss0 = ss0;
            tss_entry.esp0 = esp0;

            tss_entry.cs = 0x0b;
            tss_entry.ss = tss_entry.ds 
                = tss_entry.es 
                = tss_entry.fs 
                = tss_entry.gs 
                = 0x13;
        }

        void set_kernel_stack(uint32_t stack)
        {
            tss_entry.esp0 = stack;
        }
    } // !namespace
} // !namespace