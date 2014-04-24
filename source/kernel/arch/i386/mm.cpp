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
// mm.cpp - memory manager
//

#include <kernel/mm.h>
#include <kernel/memory.h>

namespace mirus
{
    uint32_t* page_directory = (uint32_t*)PAGE_DIRECTORY_VIRTUAL_ADDRESS;
    uint32_t* page_tables    = (uint32_t*)PAGE_TABLE_VIRTUAL_ADDRESS;

    page_directory_t* current_directory;
    uint32_t location = 0x200000;

    void alloc_page()
    {
        uint32_t l = location;
        location = (uint32_t)location + 0x1000;
        return l;
    }

    void free_page()
    {
        
    }

    void init_paging(uint32_t memory_size, unsigned int end)
    {
        /*
            It's simple!

            Copy the location of your page directory into the CR3 register.
            Set the PG bit in the CR0 register. (OR-ing with 0x80000000.)
        */

        uint32_t cr0;

        // TODO: page fault handler


    }
} // !namespace