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
// isr.hpp - isr implimentation
//

#pragma once

#include <stdafx.hpp>
#include <cpu/idt.hpp>
#include <cpu/regs.hpp>

namespace mirus
{
    namespace cpu
    {
         // triggered when a kernel panic happens
        extern "C" void fault_handler(struct regs* r);

        // isr functions
        class isr
        {
            public:
                // install the isr controller
                static void install();
        };
    } // !namespace
} // !namespace