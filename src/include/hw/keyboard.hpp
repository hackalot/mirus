#ifndef _MIRUS_KERNEL_KEYBOARD_HPP_
#define _MIRUS_KERNEL_KEYBOARD_HPP_

#include <cpu/register.hpp>
#include <misc/printf.hpp>
#include <core/ioport.hpp>
#include <cpu/irq.hpp>
#include <stddef.h>
#include <stdint.h>
#include <term/terminal.hpp>

namespace mirus {
    void keyboard_handler(struct regs* r);
    void keyboard_install();
}

#endif