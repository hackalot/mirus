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

#include <stdint.h>
#include <stddef.h>
#include <lib/stdio.h>
#include <kernel/syscall.h>
#include <kernel/irq.h>
#include <kernel/isr.h>

namespace mirus
{
    const uint32_t MAX_SYSCALLS = 1;
    typedef uint32_t (*syscall_t)(...);

    uint32_t sys_sendmsg(uint32_t dest, uint32_t sender)
    {
        kprintf("dest:%d sender:%d\n", dest, sender);
        return 0;
    }

    uint32_t sys_spawn()
    {
        return 0;
    }

    uintptr_t syscalls[MAX_SYSCALLS] =
    {
        (uintptr_t)&sys_sendmsg
    };

    void syscall_handler(regs* r)
    {
        if (r->eax >= MAX_SYSCALLS)
        {
            return;
        }

        uintptr_t location = syscalls[r->eax];
        if (!location)
        {
            return;
        }

        // TODO: GPF when trying to get call return value, re-implement
        syscall_t func = (syscall_t)location;
        func(r->ebx, r->ecx, r->edx, r->esi, r->edi);
    }

    void init_syscalls()
    {
        irq::install_handler(0x7F, syscall_handler);
    }
} // !namespace