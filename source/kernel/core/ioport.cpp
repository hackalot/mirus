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

#include <core/ioport.hpp>

unsigned char mirus::inb(unsigned short _port)
{
    unsigned char rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void mirus::outb(unsigned short _port, unsigned char _data)
{
    asm volatile ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
