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
//

#include <kernel/multiboot.h>
#include <kernel/screen.h>

namespace mirus
{
    //
    // kernel_main - our kernel entry point
    //
    extern "C" void kernel_main(multiboot_info_t* mbd, unsigned int magic)
    {
        Screen screen = {};
        screen.init();
        screen.write('a');
        while (true);
    }
} // !namespace