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
// screen.cpp - VGA text mode
//

#include <screen/screen.hpp>

namespace mirus
{
    namespace screen
    {
        void screen::install()
        {
            screen::video_memory = (signed int*)0xB8000;
            screen::rows = 25;
            screen::cols = 25;
            screen::x_pos = 0;
            screen::y_pos = 0;
        }

        void screen::set_color(vga_color color)
        {

        }

        int screen::make_entry(vga_color color,
            char c)
        {
            int c16 = c;
            int color16 = (int)color;

            return c16 | color16 << 8;
        }
    } // !namespace
} // !namespace