#ifndef _MIRUS_KERNEL_KEYBOARD_HPP_
#define _MIRUS_KERNEL_KEYBOARD_HPP_

#include <cpu/register.hpp>
#include <misc/printf.hpp>
#include <core/ioport.hpp>
#include <cpu/irq.hpp>
#include <stddef.h>
#include <stdint.h>
#include <term/terminal.hpp>

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

typedef struct keymap {
  // All the chars mapped to their respective scancodes
  uint8_t scancodes[128];
  uint8_t shift_scancodes[128];

  // The function keys mapped to the bit position in the key status map.
  uint8_t control_map[8];

  // The statuses of the control keys, initialized to 0
  key_status_t controls;
} keymap_t;


namespace mirus {
    extern "C" void keyboard_handler(struct regs* r);
    void keyboard_install();
}

#endif