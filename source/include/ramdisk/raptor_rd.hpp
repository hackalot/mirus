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
// raptor_rd.hpp - Raptor ramdisk
//

#pragma once

#include <stdafx.hpp>

namespace mirus
{
    namespace boot
    {
        enum class raptor_inode_type : int
        {
            null = 0x00,
            file = 0x01,
            pipe = 0x02,
            dir  = 0x03
        };

        enum class raptor_inode_flags : int
        {
            ro         = 0x00,
            hidden     = 0x01,
            compressed = 0x02,
            encrypted  = 0x03
        };

        class raptor_inode
        {
        public:
            char name[256];
            uint8_t   type;
            uint8_t   flags;
            uint8_t   permissions;
            uintptr_t blocks[256];
        };

        class raptor_block
        {
        public:
            uint32_t data[512];
        };

        class raptor_superblock
        {
        public:
            int8_t fs_magic;
            uint8_t fs_version;
            uint32_t inode_count;
            uint32_t used_inode_count;
        };

        class raptor_ramdisk
        {
        public:
            const uint32_t sb_offset = 0;
            const uint32_t sb_length = 1024;
            
            raptor_superblock* sb = nullptr;
            raptor_inode inodes[1024];
        };

        raptor_ramdisk* rd = nullptr;

        void read_ramdisk(uint32_t location)
        {
            raptor_superblock* sb = (raptor_superblock*)location;
            ktrace(trace_level::log, "Magic: %x\n", sb->fs_magic);
        }
    } // !namespace
} // !namespace