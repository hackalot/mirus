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
// syscall.cpp - System call implementation
//

#include <stdafx.hpp>
#include <system/syscall.hpp>
#include <cpu/irq.hpp>
#include <cpu/isr.hpp>

namespace mirus
{
    namespace system
    {
        const uint32_t MAX_SYSCALLS = 1;
        typedef uint32_t (*syscall_t)(...);

        uint32_t sys_sendmsg(pid_t dest, pid_t sender)
        {
            kprintf("dest:%d sender:%d\n", dest, sender);
            return 0;
        }

        uintptr_t syscalls[MAX_SYSCALLS] =
        {
            (uintptr_t)&sys_sendmsg
        };

        void syscall_handler(cpu::regs* r)
        {
            ktrace(trace_level::msg, "System call called\n");
            ktrace(trace_level::msg, "Syscall number: %x\n", r->eax);

            if (r->eax >= MAX_SYSCALLS)
            {
                ktrace(trace_level::error, "Could not call: Out of bounds\n");
                return;
            }

            uintptr_t location = syscalls[r->eax];
            if (!location)
            {
                ktrace(trace_level::error, "Could not call: Non existant\n");
                return;
            }

            ktrace(trace_level::msg, "eax:%d ebx:%d edx:%d esi:%d edi:%d\n",
                r->eax, r->ebx, r->ecx, r->edx, r->esi, r->edi);

            // TODO: GPF when trying to get call return value, re-implement
            syscall_t func = (syscall_t)location;
            func(r->ebx, r->ecx, r->edx, r->esi, r->edi);
        }

        void init_syscalls()
        {
            cpu::irq::install_handler(0x7F, syscall_handler);
        }
    } // !namespace
} // !namespace