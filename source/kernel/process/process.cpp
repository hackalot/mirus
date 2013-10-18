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
// process.cpp - process information
//

#include <process/process.hpp>

namespace mirus
{
    namespace system
    {
        //
        // jmp_usermode - Jump to usermode
        //
        extern "C" void jump_usermode();

        // 
        // enter_userpace - Goodbye kernel
        //
        void enter_userspace(uintptr_t location)
        {
            ktrace(trace_level::warning, "ENTERING USERSPACE\n");

            asm volatile(
                "mov $0x23, %%ax\n"
                "mov %%ax, %%ds\n"
                "mov %%ax, %%es\n"
                "mov %%ax, %%fs\n"
                "mov %%ax, %%gs\n"
                "mov %%esp, %%eax\n"
                "push $0x23\n"
                "push %%eax\n"
                "pushf\n"
                "push $0x1B\n"
                "push %0\n"
                "iret\n"
                : "=r"(location));

            ktrace(trace_level::log, "Done\n");
        }
    } // !namespace
} // !namespace