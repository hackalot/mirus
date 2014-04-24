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
// mm.h - memory manager
//

#pragma once

#include <stddef.h>
#include <stdint.h>

// TODO: physical memory manager needed in kernel mode, or only paging?

namespace mirus
{
    #define PAGE_DIRECTORY_VIRTUAL_ADDRESS 0xFFBFF000
    #define PAGE_TABLE_VIRTUAL_ADDRESS     0xFFC00000

    #define PAGE_DIRECTORY_INDEX(x) ((uint32_t)x/1024)
    #define PAGE_TABLE_INDEX(x) ((uint32_t)x%1024)

    #define PAGE_PRESENT 0x1
    #define PAGE_WRITE   0x2
    #define PAGE_USER    0x4
    #define PAGE_MASK    0xFFFFF000

    #define PAGE_SIZE    0x1000

    typedef uint32_t page_directory_t;

    void init_paging(uint32_t memory_size, unsigned int end);
    void switch_page_directory(page_directory_t* dir);
    void map(uint32_t virt_addr, uint32_t phys_addr, uint32_t flags);
    void unmap(uint32_t virt_addr);
} // !namespace