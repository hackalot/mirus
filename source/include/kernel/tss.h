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
// tss.h - Task state segment
//

#pragma once

#include <stdint.h>
#include <stddef.h>

namespace mirus
{
    extern "C" void tss_flush();

    //
    // tss_entry_t - Describes a task state segment
    //
    class tss_entry_t
    {
    public:
        uint32_t prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
        uint32_t esp0;       // The stack pointer to load when we change to kernel mode.
        uint32_t ss0;        // The stack segment to load when we change to kernel mode.
        uint32_t esp1;       // Unused...
        uint32_t ss1;
        uint32_t esp2;
        uint32_t ss2;
        uint32_t cr3;
        uint32_t eip;
        uint32_t eflags;
        uint32_t eax;
        uint32_t ecx;
        uint32_t edx;
        uint32_t ebx;
        uint32_t esp;
        uint32_t ebp;
        uint32_t esi;
        uint32_t edi;
        uint32_t es;         // The value to load into ES when we change to kernel mode.
        uint32_t cs;         // The value to load into CS when we change to kernel mode.
        uint32_t ss;         // The value to load into SS when we change to kernel mode.
        uint32_t ds;         // The value to load into DS when we change to kernel mode.
        uint32_t fs;         // The value to load into FS when we change to kernel mode.
        uint32_t gs;         // The value to load into GS when we change to kernel mode.
        uint32_t ldt;        // Unused...
        uint16_t trap;
    } __attribute__((packed));

    //
    // tss - Handles task switching functions
    //
    class tss
    {
    public:
        static void write(int32_t num, uint16_t ss0, uint32_t esp0);
    };

    void set_kernel_stack(uint32_t stack);
} // !namespace