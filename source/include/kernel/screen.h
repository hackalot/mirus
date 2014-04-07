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
// screen.h - Generic screen drawing functions
//

#pragma once

#ifdef __ARCH_I386__
    #include <arch/i386/screen.h>
#endif

namespace mirus
{
    class Screen
    {
    public:
        // Set up the screen
        static void init();

        //
        // Screen printing functions
        //
        static void write(char c);
        static void write(int i);
        static void write(const char* c);
        static void writeln(char* c);

        //
        // Utility functions
        //
        static void move_cursor();
        static void clear();
        static void scroll();
    };
} // !namespace