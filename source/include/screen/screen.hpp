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
        enum class vga_color : int
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

        class screen
        {
            public:
                // set up the screen
                void install();

                // set color
                void set_color(vga_color color);

                // make an entry
                signed int make_entry(vga_color color, 
                    char c);

                // put entry
                void put_entry(char c, 
                    vga_color color, 
                    int x, 
                    int y);

                // write to the screen, don't flush
                template<class T>
                void write(T val)
                {
                    if (val == '\r')
                    {
                        y_pos++;
                        x_pos = 0;
                    }
                    else if (val == '\b')
                    {
                        x_pos--;
                        screen::put_entry(' ', term_color, x_pos, y_pos);
                    }
                    else
                    {
                        screen::put_entry(val, term_color, x_pos, y_pos);
                    }

                    move_cursor();
                }

                // write to screen, flush
                template <class T>
                void writeln(T val)
                {
                    write(val);
                    write('\n');
                }

                // move cursor
                void move_cursor();

                // clear it
                void clear();

            private:
                signed int* video_memory;
                int term_color = 0;

                int rows = 25;
                int cols = 80;

                int x_pos = 0;
                int y_pos = 0;
        };
    } // !namespace
} // !namespace