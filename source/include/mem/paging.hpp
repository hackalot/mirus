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
// paging.hpp - interface for paging and related structures
//

#pragma once

#include <stdafx.hpp>
#include <cpu/isr.hpp>

namespace mirus
{
    namespace mem
    {
        typedef struct page
        {
            uint32_t present    : 1;   // Page present in memory
            uint32_t rw         : 1;   // Read-only if clear, readwrite if set
            uint32_t user       : 1;   // Supervisor level only if clear
            uint32_t accessed   : 1;   // Has the page been accessed since last refresh?
            uint32_t dirty      : 1;   // Has the page been written to since last refresh?
            uint32_t unused     : 7;   // Amalgamation of unused and reserved bits
            uint32_t frame      : 20;  // Frame address (shifted right 12 bits)
        } page_t;

        typedef struct page_table
        {
            page_t pages[1024];
        } page_table_t;

        typedef struct page_directory
        {
            page_table_t* tables[1024];
            uint32_t tables_physical[1024];
            uint32_t physical_address;
        } page_directory_t;

        class paging
        {
        public:
            static void init(uint32_t memsize);
            static void switch_page_directory(page_directory_t* new_dir);
            static page_t* get_page(uint32_t address, int make, page_directory_t* dir);
            static void page_fault(cpu::regs* r);
        };
    } // !namespace
} // !namespace