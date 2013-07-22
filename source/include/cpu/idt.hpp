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

#ifndef _MIRUS_KERNEL_IDT_H_
#define _MIRUS_KERNEL_IDT_H_

#include <mem/memory.hpp>
#include <util/debug.hpp>

namespace mirus
{
    // defines an entry in our idt
    class idt_entry
    {
        public:
            unsigned short base_lo;
            unsigned short sel;        // Our kernel segment goes here!
            unsigned char always0;     // This will ALWAYS be set to 0!
            unsigned char flags;       // Set using the above table!
            unsigned short base_hi;
    } __attribute__ ((__packed__));

    // pointer to our idt
    class idt_ptr
    {
        public:
            unsigned short limit;
            unsigned long base;
    } __attribute__ ((__packed__));

    // idt and idt functions
    class idt
    {
        public:
            // setup an idt entry
            static void set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
            
            // install the idt
            static void install();
    };
}

#endif
