// Copyright (c) 2013 Joshua Beitler, Mirus contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <stddef.h>
#include <stdint.h>

#define IS_PAGE_ALIGNED(x) ((  ((uint32_t)(x)) & 0x00000fff) == 0)
#define IS_DWORD_ALIGNED(x) (( ((uint32_t)(x)) & 3) == 0)

#define HEAP_MAGIC 0xabcdef12

#define AREA_USED 0
#define AREA_FREE 1

#define FOOTER_FROM_HEADER(__h) ((area_footer_t *)((uint32_t)__h + __h->size - sizeof(area_footer_t)))

#define HEAP_INDEX_SIZE 0x10000

#define KHEAP_START 0xc0000000
#define KHEAP_MAX_ADDR 0xcffff000 /* one page less than 0xd000000 */

/* Values for heap debugging */
#define KHEAP_INITIAL_SIZE 0x90000 /* 64 kiB + 512k for the indexes */
#define KHEAP_MIN_GROWTH 0x8000 /* 32 kiB */
#define KHEAP_MAX_WASTE 0x120000 /* must be >1 MiB */

#define USER_HEAP_INITIAL_SIZE 0x90000
#define USER_HEAP_MIN_GROWTH 0x8000
#define USER_HEAP_MAX_WASTE 0x120000

#define USER_HEAP_START 0x20000000
#define USER_HEAP_MAX_ADDR 0xbff00000

namespace mirus {
    typedef struct {
        uint32_t size; /* includes the header and footer! */
        uint8_t type; /* == AREA_USED (0) || AREA_FREE (1) */
        uint32_t magic;
    } area_header_t;

    typedef struct {
        uint32_t magic;
        area_header_t *header;
    } area_footer_t;

    typedef struct {
        uint32_t start_address;
        uint32_t end_address;
        uint32_t _min_address; // start address is for the storage; _min_address for the entire heap w/ indexes etc.
        uint32_t max_address;
        uint8_t supervisor;
        uint8_t readonly;

        ordered_array_t free_index; /* Stores an array of area_header_t pointers */
        ordered_array_t used_index; /* Stores an array of area_header_t pointers */

        area_header_t *rightmost_area; /* A pointer to the rightmost area, free or used. Used in both alloc() and free(). */

        mutex_t *mutex;
    } heap_t;

    void stop_leak_trace(void);
    void start_leak_trace(void);

    heap_t *heap_create(uint32_t start_address, uint32_t initial_size, uint32_t max_address, uint8_t supervisor, uint8_t readonly, struct task_mm *mm);
    void heap_destroy(heap_t *heap, page_directory_t *dir);
    void *heap_alloc(uint32_t size, bool page_align, heap_t *heap);
    void heap_free(void *p, heap_t *heap);

    void validate_heap_index(bool print_headers);
    void print_heap_index(void);


    void kfree(void* p);

    void* malloc(size_t);
    void free(void*);

    void kmalloc_int(uint32_t size, bool align, uint32_t* phys);
    void* kmalloc(uint32_t size);
    void* kmalloc_a(uint32_t size);
    void* kmalloc_p(uint32_t size, uint32_t* phys);
    void* kmalloc_ap(uint32_t size, uint32_t* phys);

    void* krealloc(void* p, size_t new_size);
}