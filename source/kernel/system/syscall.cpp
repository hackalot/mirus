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
// syscall.cpp - System call implimentation
//

#include <stdafx.hpp>
#include <system/syscall.hpp>
#include <cpu/irq.hpp>

namespace mirus
{
    namespace system
    {
        static uint32_t test_syscall()
        {
            kprintf("Test syscall called.\n");
        }

        static uintptr_t syscalls[] =
        {
            (uintptr_t)&test_syscall
        };

        typedef uint32_t (*syscall_t)(unsigned int, ...);

        void syscall_handler(cpu::regs* r)
        {
            ktrace(trace_level::log, "System call called\n");
            if (r->eax >= 3)
                return;

            uintptr_t location = syscalls[r->eax];
            if (!location)
                return;

            syscall_t func = (syscall_t)location;
            uint32_t ret = func(r->ebx, r->ecx, r->edx, r->esi, r->edi);

            r->eax = ret;
        }

        void test_syscalls(int eax)
        {
            cpu::regs* r;
            r->eax = eax;
            syscall_handler(r);
        }

        void init_syscalls()
        {
            // asm volatile("sti");
            cpu::irq::install_handler(0x80, &syscall_handler);
        }
    } // !namespace
} // !namespace