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

// TODO: move under a hw::keyboard class

namespace mirus
{
    // triggered on keypress
    void keyboard_handler(struct regs *r);
    
    // install the keyboard
    void keyboard_install();

    // get char
    char keyboard_getkey();
}

#endif
