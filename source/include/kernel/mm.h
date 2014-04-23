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
    void init_paging(uint32_t memory_size, unsigned int end);
} // !namespace