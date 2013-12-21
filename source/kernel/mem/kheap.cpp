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
// kheap.cpp - kernel heap
//

#include <mem/kheap.hpp>

namespace mirus
{
    namespace mem
    {
        extern "C" uint32_t end;
        uint32_t placement_address = (uint32_t)&end;

        uint32_t kmalloc_int(uint32_t size, int align, uint32_t* phys)
        {
            if (align == 1 && (placement_address & 0xFFFFF000))
            {
                placement_address &= 0xFFFFF000;
                placement_address += 0x1000;
            }

            if (phys)
            {
                *phys = placement_address;
            }

            uint32_t temp = placement_address;
            placement_address += size;

            return temp;
        }

        uint32_t kmalloc_a(uint32_t size)
        {
            return kmalloc_int(size, 1, 0);
        }

        uint32_t kmalloc_p(uint32_t size, uint32_t* phys)
        {
            return kmalloc_int(size, 0, phys);
        }

        uint32_t kmalloc_ap(uint32_t size, uint32_t* phys)
        {
            return kmalloc_int(size, 1, phys);
        }

        uint32_t kmalloc(uint32_t size)
        {
            return kmalloc_int(size, 0, 0);
        }
    } // !namespace
} // !namespace