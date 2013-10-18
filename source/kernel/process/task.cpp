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
// task.cpp - Task stuff
//

#include <process/task.hpp>

namespace mirus
{
    namespace system
    {
        //
        // enter_userpace - Goodbye kernel
        //
        void enter_userspace()
        {
            ktrace(trace_level::warning, "ENTERING USERSPACE\n");

        // Set up a stack structure for switching to user mode.
        asm volatile("\
            cli;\
            mov $0x23, %ax;\
            mov %ax, %ds;\
            mov %ax, %es;\
            mov %ax, %fs;\
            mov %ax, %gs;\
                  \
            mov %esp, %eax;\
            pushl $0x23;\
            pushl %eax;\
            pushf;\
            pushl $0x1B;\
            push $1f;\
            iret;\
          1:\
            ");

            ktrace(trace_level::log, "Done\n");
        }
    } // !namespace
} // !namespace