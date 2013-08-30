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
// idt.hpp - idt implimentation
//

#pragma once

namespace mirus
{
    namespace cpu
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
                static void set_gate(unsigned char num, 
                    unsigned long base, 
                    unsigned short sel, 
                    unsigned char flags);
                
                // install the idt
                static void install();
        };
    } // !namespace
} // !namespace