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
#include <util/asm.hpp>
#include <util/ports.hpp>
#include <util/string.hpp>

using mirus::hardware::io::inb;
using mirus::hardware::io::outb;  

namespace mirus
{
    namespace screen
    {
        unsigned short *textmemptr;
        int attrib = 0x0F;
        int csr_x = 0, csr_y = 0;

        // clear the screen
        void terminal::clear()
        {
            unsigned blank = 0x20 | (attrib << 8);

            for(auto i = 0; i < 25; i++)
                memsetw(textmemptr + i * 80, blank, 80);

            csr_x = 0;
            csr_y = 0;
            
            move_cursor();         
        }

        // move hardware cursor
        void terminal::move_cursor()
        {
            unsigned temp = temp = csr_y * 80 + csr_x;

            outb(0x3D4, 14);
            outb(0x3D5, temp >> 8);
            outb(0x3D4, 15);
            outb(0x3D5, temp);
        }

        // drop a new line if needed
        void terminal::scroll()
        {
            unsigned blank, temp;

            blank = 0x20 | (attrib << 8);

            if (csr_y >= 25)
            {
                temp = csr_y - 25 + 1;
                memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);
                memsetw (textmemptr + (25 - temp) * 80, blank, 80);
                csr_y = 25 - 1;
            }   
        }

        // set current color
        void terminal::set_color(unsigned char fg,
            unsigned char bg)
        {
            attrib = (bg << 4) | (fg & 0x0F);
        }

        // printing functions
        void terminal::write(char val)
        {
            unsigned short *where;
            unsigned att = attrib << 8;

            // backspace
            if (val == 0x08)
            {
                if (csr_x != 0) 
                    csr_x--;
            }

            // tab
            else if (val == 0x09)
                csr_x = (csr_x + 8) & ~(8 - 1);

            // carriage return
            else if (val == '\r')
                csr_x = 0;

            // newline
            else if (val == '\n')
            {
                csr_x = 0;
                csr_y++;
            }

            else if (val >= ' ')
            {
                where = textmemptr + (csr_y * 80 + csr_x);
                *where = val | att;
                
                csr_x++;
            }

            // scroll to new line if needed
            if (csr_x >= 80)
            {
                csr_x = 0;
                csr_y++;
            }

            scroll();
            move_cursor();
        }

        void terminal::write(const char* val)
        {
            for (size_t i = 0; i < strlen(val); i++)
                terminal::write(val[i]);
        }

        void terminal::write(int val)
        {
            terminal::write(iota(val));
        }

        void terminal::writeln(const char* val)
        {
            terminal::write(val);
            terminal::write('\n');
        }
        
        void terminal::set_col(int x)
        {
            csr_x = x;
            move_cursor();
        }

        void terminal::set_row(int y)
        {
            csr_y = y;
            move_cursor();
        }

        // set up our terminal
        void terminal::install()
        {
            textmemptr = (unsigned short *)0xB8000;
            terminal::set_color((unsigned char)vga_color::white,
                (unsigned char)vga_color::black);
            terminal::clear();
        }
    } // !namespace
} // !namespace