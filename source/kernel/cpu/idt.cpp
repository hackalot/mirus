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
// idt.cpp - idt implimentation
//

#include <cpu/idt.hpp>

namespace mirus
{
    namespace cpu
    {
        extern "C"
        {
            void idt_load();
            idt_ptr idtp;
        }

        // IDT entry table
        static idt_entry _idt[256];

        //
        // set an entry in the idt
        //
        void idt::set_gate(unsigned char num, 
            unsigned long base, 
            unsigned short sel, 
            unsigned char flags)
        {
            // interrupt base routine address
            _idt[num].base_lo = (base & 0xFFFF);
            _idt[num].base_hi = (base >> 16) & 0xFFFF;

            // segment selection and flags
            _idt[num].sel = sel;
            _idt[num].always0 = 0;
            _idt[num].flags = flags;
        }

        //
        // Install IDT + get ready for use
        //
        void idt::install()
        {
            // set up IDT pointer
            idtp.limit = (sizeof(idt_entry) * 256) - 1;
            idtp.base = (unsigned long)&_idt;

            // clear IDT
            memset((unsigned char *)&_idt, 0, sizeof(idt_entry) * 256);

            // load idt
            idt_load();
        }
    } // !namespace
} // !namespace