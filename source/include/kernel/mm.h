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

//! 8 blocks per byte
#define PMMNGR_BLOCKS_PER_BYTE 8
 
//! block size (4k)
#define PMMNGR_BLOCK_SIZE   4096
 
//! block alignment
#define PMMNGR_BLOCK_ALIGN  PMMNGR_BLOCK_SIZE

//! size of physical memory
static  uint32_t    _mmngr_memory_size=0;
 
//! number of blocks currently in use
static  uint32_t    _mmngr_used_blocks=0;
 
//! maximum number of available memory blocks
static  uint32_t    _mmngr_max_blocks=0;
 
//! memory map bit array. Each bit represents a memory block
static  uint32_t*   _mmngr_memory_map= 0;

inline void mmap_set (int bit) {
  _mmngr_memory_map[bit / 32] |= (1 << (bit % 32));
}

inline void mmap_unset (int bit) {
 
  _mmngr_memory_map[bit / 32] &= ~ (1 << (bit % 32));
}

inline bool mmap_test (int bit) {
 
 return _mmngr_memory_map[bit / 32] &  (1 << (bit % 32));
}

int mmap_first_free () {
 
    //! find the first free bit
    for (uint32_t i=0; i< pmmngr_get_block_count() / 32; i++)
        if (_mmngr_memory_map[i] != 0xffffffff)
            for (int j=0; j<32; j++) {      //! test each bit in the dword
 
                int bit = 1 << j;
                if (! (_mmngr_memory_map[i] & bit) )
                    return i*4*8+j;
            }
 
    return -1;
}

void    pmmngr_init (size_t memSize, physical_addr bitmap) {
 
    _mmngr_memory_size  =   memSize;
    _mmngr_memory_map   =   (uint32_t*) bitmap;
    _mmngr_max_blocks   =   (pmmngr_get_memory_size()*1024) / PMMNGR_BLOCK_SIZE;
    _mmngr_used_blocks  =   pmmngr_get_block_count();
 
    //! By default, all of memory is in use
    memset (_mmngr_memory_map, 0xf, pmmngr_get_block_count() / PMMNGR_BLOCKS_PER_BYTE );
}

void    pmmngr_init_region (physical_addr base, size_t size) {
 
    int align = base / PMMNGR_BLOCK_SIZE;
    int blocks = size / PMMNGR_BLOCK_SIZE;
 
    for (; blocks>0; blocks--) {
        mmap_unset (align++);
        _mmngr_used_blocks--;
    }
 
    mmap_set (0);   //first block is always set. This insures allocs cant be 0
}

void    pmmngr_deinit_region (physical_addr base, size_t size) {
 
    int align = base / PMMNGR_BLOCK_SIZE;
    int blocks = size / PMMNGR_BLOCK_SIZE;
 
    for (; blocks>0; blocks--) {
        mmap_set (align++);
        _mmngr_used_blocks++;
    }
}

void*   pmmngr_alloc_block () {
 
    if (pmmngr_get_free_block_count() <= 0)
        return 0;   //out of memory
 
    int frame = mmap_first_free ();
 
    if (frame == -1)
        return 0;   //out of memory
 
    mmap_set (frame);
 
    physical_addr addr = frame * PMMNGR_BLOCK_SIZE;
    _mmngr_used_blocks++;
 
    return (void*)addr;
}

void    pmmngr_free_block (void* p) {
 
    physical_addr addr = (physical_addr)p;
    int frame = addr / PMMNGR_BLOCK_SIZE;
 
    mmap_unset (frame);
 
    _mmngr_used_blocks--;
}