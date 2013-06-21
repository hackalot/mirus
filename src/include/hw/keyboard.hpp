// Copyright (c) 2013 Joshua Beitler, Mirus contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef _MIRUS_KERNEL_KEYBOARD_HPP_
#define _MIRUS_KERNEL_KEYBOARD_HPP_

#include <cpu/register.hpp>
#include <misc/printf.hpp>
#include <core/ioport.hpp>
#include <cpu/irq.hpp>
#include <stddef.h>
#include <stdint.h>
#include <term/terminal.hpp>
#include <util/debug.hpp>

#define CONTROL 0x1
#define ALT 0x2
#define ALTGR 0x4
#define LSHIFT 0x8
#define RSHIFT 0x10
#define CAPSLOCK 0x20
#define SCROLLLOCK 0x40
#define NUMLOCK 0x80

#define RMASK 0x80;

typedef uint8_t key_status_t;

typedef struct keymap
{
    // All the chars mapped to their respective scancodes
    uint8_t scancodes[128];
    uint8_t shift_scancodes[128];

    // The function keys mapped to the bit position in the key status map.
    uint8_t control_map[8];

    // The statuses of the control keys, initialized to 0
    key_status_t controls;
} keymap_t;


namespace mirus
{
    void keyboard_handler(struct regs *r);
    void keyboard_install();

    char keyboard_getkey();
}

#endif
