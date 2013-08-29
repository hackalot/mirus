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
// gdt.hpp - gdt implimentation
//

#pragma once

namespace mirus
{
    // defines an entry in the gdt
    class gdt_entry
    {
        public:
            unsigned short limit_low;
            unsigned short base_low;
            unsigned char base_middle;
            unsigned char access;
            unsigned char granularity;
            unsigned char base_high;
    } __attribute__ ((__packed__));

    // pointer to our gdt
    class gdt_ptr
    {
        public:
            unsigned short limit;
            unsigned long base;
    } __attribute__ ((__packed__));

    // our gdt + functions
    class gdt
    {
        public:
            // setup a new entry
            static void set_gate(int num, 
                unsigned long base, 
                unsigned long limit, 
                unsigned char access, 
                unsigned char gran);
            
            // install the gdt
            static void install();
    };
}