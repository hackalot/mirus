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
// alloc.hpp - joshbeitler's home-grown, organic stack allocator
//			   explaination avalible on wiki
//

#pragma once

namespace mirus
{
	namespace memory
	{
		class stack_allocator
		{
		public:
			// Install the stack allocator, perform basic
			// initilization functions
			static void install(size_t memory_size, 
				unsigned int* kernel_start,
				unsigned int* kernel_end,
				size_t block_size);

			// Allocate a region of memory
			static void k_alloc(size_t size);

			// Free a region of memory
			static void k_free(void* val);
		};
	} // !namespace
} // !namespace