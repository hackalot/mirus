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

#include <hw/keyboard.hpp>

keymap_t us =
{
    //normal keys
    {
        /* first row - indices 0 to 14 */
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',

        /* second row - indices 15 to 28 */
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\r', //Enter key

        /* 29 = Control, 30 - 41: third row */
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',

        /* fourth row, indices 42 to 54, zeroes are shift-keys*/
        0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,

        '*',

        /* Special keys */

        0, //ALT - 56
        ' ', // Space - 57
        0, //Caps lock - 58
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // F1 to F10 - 59 to 68
        0, //Num lock - 69
        0, //Scroll lock - 70
        0, //Home - 71
        0, //Up arrow - 72
        0, //Page up - 73
        '-',
        0, //Left arrow - 75
        0,
        0, //Right arrow -77
        '+',
        0, //End - 79
        0, //Dowm arrow - 80
        0, //Page down - 81
        0, //Insert - 82
        0, //Delete - 83
        0, 0, 0,
        0, //F11 - 87
        0, //F12 - 88
        0, //All others undefined
    },
    //caps
    {
        /* first row - indices 0 to 14 */
        0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',

        /* second row - indices 15 to 28 */
        '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\r', //Enter key

        /* 29 = Control, 30 - 41: third row */
        0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',

        /* fourth row, indices 42 to 54, zeroes are shift-keys*/
        0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,

        '*',

        /* Special keys */

        0, //ALT - 56
        ' ', // Space - 57
        0, //Caps lock - 58
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // F1 to F10 - 59 to 68
        0, //Num lock - 69
        0, //Scroll lock - 70
        0, //Home - 71
        0, //Up arrow - 72
        0, //Page up - 73
        '-',
        0, //Left arrow - 75
        0,
        0, //Right arrow -77
        '+',
        0, //End - 79
        0, //Dowm arrow - 80
        0, //Page down - 81
        0, //Insert - 82
        0, //Delete - 83
        0, 0, 0,
        0, //F11 - 87
        0, //F12 - 88
        0, //All others undefined
    },

    // control_map
    {
        29, // Ctrl
        56, // Alt
        0,  // AltGr
        42, // left Shift
        54, // right Shift
        58, // Caps lock
        70, // Scroll lock
        69  // Num lock
    },

    //Set the initial status of all control keys to "not active"
    0
};

keymap_t* current_layout;
char c;

void mirus::keyboard_handler(struct regs* r)
{
    unsigned char scancode;
    scancode = mirus::inb(0x60);

    if (scancode & 0x80)
    {
        // TODO: handle control keys
    }
    else
    {
        uint8_t* scancodes = current_layout->scancodes;

        // ERROR: doesn't work
        if ((current_layout->controls & (LSHIFT | RSHIFT | CAPSLOCK)) && !(current_layout->controls & CONTROL))
        {
            scancodes = current_layout->shift_scancodes;
        }

        c = scancodes[scancode];
        mirus::terminal_putchar(scancodes[scancode]);

        mirus::keyboard_getkey();
    }

    mirus::irq::ack(1);
}

char mirus::keyboard_getkey()
{
    return c;
}

void mirus::keyboard_install()
{
    mirus::irq::install_handler(1, keyboard_handler);
    current_layout = &us;

    mirus::irq::ack(1);
}

