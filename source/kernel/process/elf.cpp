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
// elf.cpp - ELF loader
//

#include <stdafx.hpp>
#include <process/elf.hpp>

namespace mirus
{
	namespace system
	{
        int exec(uint32_t address)
        {
            ktrace(trace_level::none, "--- Elf load started ---\n");
            Elf32_Header* header = (Elf32_Header*)address;

            if (header->e_ident[0] != ELFMAG0 ||
                header->e_ident[1] != ELFMAG1 ||
                header->e_ident[2] != ELFMAG2 ||
                header->e_ident[3] != ELFMAG3) 
            {
                ktrace(trace_level::error, "Not a valid ELF executable\n");
            }
            else
            {
                ktrace(trace_level::log, "ELF magic checks out\n");
            }

            ktrace(trace_level::none, "--- Elf load ended ---\n");
        }
	} // !namespace
} // !namespace