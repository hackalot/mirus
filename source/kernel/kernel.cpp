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
// kernel.cpp - main source file + kernel entry point
//              we all have to begin somewhere, right?
//

#include <stdafx.hpp>
#include <boot/multiboot.hpp>

#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/isr.hpp>
#include <cpu/irq.hpp>

#include <screen/screen.hpp>

namespace mirus
{
    //      We are now entering kernel mode.
    //      No libraries, only stuff we have made.
    //      This is man's land.
    //      No fucking "cowsay" or "fortune" to
    //      help brighten our days
    //
    // - joshbeitler
    extern "C" void kernel_main(multiboot_info_t* mbd, 
        unsigned int magic)
    {
        // Install CPU hardware devices
        cpu::gdt::install();
        cpu::idt::install();
        cpu::isr::install();
        cpu::irq::install();

        // Set up screen
        screen::terminal::install();

        // Do some tests
        screen::terminal::writeln("hello");
        screen::terminal::write("world");

        while (true);
    }
} // !namespace
