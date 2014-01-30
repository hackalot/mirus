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
// paging.hpp - Paging implementation
//

#pragma once

#include <stdafx.hpp>

namespace mirus
{
	namespace system
	{
		typedef struct page
		{
			u32int present    : 1;   // Page present in memory
		    u32int rw         : 1;   // Read-only if clear, readwrite if set
		    u32int user       : 1;   // Supervisor level only if clear
		    u32int accessed   : 1;   // Has the page been accessed since last refresh?
		    u32int dirty      : 1;   // Has the page been written to since last refresh?
		    u32int unused     : 7;   // Amalgamation of unused and reserved bits
		    u32int frame      : 20;  // Frame address (shifted right 12 bits)
		} page_t;

		typedef struct page_table
		{
			page_t pages[1024];
		} page_table_t;

		typedef struct page_directory
		{
			page_table_t* tables[1024];
			uint32_t phys_tables[1024];
			uint32_t phys_addr;
		} page_directory_t;

		class paging
		{
		public:
			void init();
			void switch_page_directory(page_directory_t* new_dir);
			page_t* get_page(uint32_t addresss, int make, page_directory_t* dir);
			void page_fault(regs_t* r);
		};
	} // !namespace
} // !namespace