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
#include <kernel/memory.h>

namespace mirus
{
    unsigned short* textmemptr;

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
    void Screen::move_cursor()
    {
        unsigned temp = temp = csr_y * 80 + csr_x;

        write_byte(0x3D4, 14);
        write_byte(0x3D5, temp >> 8);
        write_byte(0x3D4, 15);
        write_byte(0x3D5, temp);
    }

    void Screen::clear()
    {
        unsigned blank = 0x20 | (attrib << 8);

        for(auto i = 0; i < 25; i++)
            memsetw(textmemptr + i * 80, blank, 80);

        csr_x = 0;
        csr_y = 0;
        
        Screen::move_cursor();
    }

    void Screen::scroll()
    {
        unsigned blank, temp;

        blank = 0x20 | (attrib << 8);

        if (csr_y >= 25)
        {
            temp = csr_y - 25 + 1;
            memcpy(textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);
            memsetw(textmemptr + (25 - temp) * 80, blank, 80);
            csr_y = 25 - 1;
        }   
    }

    void Screen::init()
    {
        textmemptr = (unsigned short*)0xB8000;
        attrib = make_color(Color::White, Color::Black);

        Screen::clear();
    }

    void Screen::write(char c)
    {
        unsigned short* where;
        unsigned att = attrib << 8;

        if (c == 0x08)
        {
            // backspace
            if (csr_x != 0) 
            {
                csr_x--;
            }
        }
        else if (c == 0x09)
        {
            // tab
            csr_x = (csr_x + 8) & ~(8 - 1);
        }
        else if (c == '\n')
        {
            // newline
            csr_x = 0;
            csr_y++;
        }
        else if (c >= ' ')
        {
            where = textmemptr + (csr_y * 80 + csr_x);
            *where = c | att;
            
            csr_x++;
        }

        // scroll to new line if needed
        if (csr_x >= 80)
        {
            csr_x = 0;
            csr_y++;
        }

        Screen::scroll();
        Screen::move_cursor();
    }

    void Screen::write(int i)
    {
        Screen::write(itoa(i));
    }

    void Screen::write(const char* c)
    {
        for (size_t i = 0; i < strlen(c); i++)
        {
            Screen::write(c[i]);
        }
    }
} // !namespace