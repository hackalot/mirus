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
// screen.h - i386 screen drawing functions
//

#include <stdint.h>
#include <kernel/screen.h>
#include <kernel/string.h>
#include <kernel/portio.h>

namespace mirus
{
    unsigned long* textmemptr;

    int attrib = 0x0F;
    int csr_x  = 0;
    int csr_y  = 0;

    //
    // Returns a bg/fg combination
    //
    unsigned char make_color(Color fg, Color bg)
    {
        return ((unsigned char)bg << 4) | ((unsigned char)fg & 0x0F);
    }

    //
    // Terminal control functions
    //
    void move_cursor()
    {
        unsigned temp = temp = csr_y * 80 + csr_x;

        outb(0x3D4, 14);
        outb(0x3D5, temp >> 8);
        outb(0x3D4, 15);
        outb(0x3D5, temp);
    }

    void Screen::init()
    {
        textmemptr = (unsigned long*)0xB8000;
        attrib = make_color(Color::White, Color::Black);
    }

    void Screen::write(const char& c)
    {
        unsigned long* where;
        unsigned att = attrib << 8;

        if (c >= ' ')
        {
            where = textmemptr + (csr_y * 80 + csr_x);
            *where = c | att;
            
            csr_x++;
        }
    }
} // !namespace