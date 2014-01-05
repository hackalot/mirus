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
// process.hpp - process information
//

#pragma once

#include <stdafx.hpp>
#include <cpu/regs.hpp>

namespace mirus
{
    namespace system
    {
        //
        // process_t - defines a process
        //
        class process_t
        {
        public:
            // Basic information
            uint32_t        pid;
            uint32_t        process_namespace;
            uint32_t        uid;
            uint32_t        umask;
            uint32_t        thread_group;
            uint32_t        job_group;
            uint32_t        session_group;
            uint8_t         status;
            uintptr_t       entry;
            uintptr_t       start;
            uint32_t        size;

            // Process information
            char**          env;
            char*           name;
            char*           desc;
            char**          cmdline;

            bool            finished;
            bool            started;

            uintptr_t       heap;
            uintptr_t       heap_actual;
            uintptr_t       stack;
            uintptr_t       user_stack;

            // CPU register state
            cpu::regs*      regstate;
        };

        // 
        // enter_userpace - Goodbye kernel
        //
        void enter_userspace(uint32_t location);
    } // !namespace
} // !namespace