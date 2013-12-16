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
// screen.hpp - VGA text mode
//

#pragma once

namespace mirus
{
    namespace screen
    {
        enum class vga_color
        {
            black         = 0,
            blue          = 1,
            green         = 2,
            cyan          = 3,
            red           = 4,
            magenta       = 5,
            brown         = 6,
            light_grey    = 7,
            dark_grey     = 8,
            light_blue    = 9,
            light_green   = 10,
            light_cyan    = 11,
            light_red     = 12,
            light_magenta = 13,
            light_brown   = 14,
            white         = 15
        };

        class terminal
        {
        public:
            // hardware functions
            static void clear();
            static void move_cursor();
            static void scroll();

            // set current color
            static void set_color(unsigned char fg,
                unsigned char bg);

            // printing functions
            static void write(char val);
            static void write(const char* val);
            static void write(int val);
            static void write(unsigned int val);
            static void writeln(const char* val);

            // location
            static void set_col(int x);
            static void set_row(int y);

            // set up
            static void install();
        };
    } // !namespace
} // !namespace