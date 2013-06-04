#ifndef _MIRUS_KERNEL_UTIL_STRING_H_
#define _MIRUS_KERNEL_UTIL_STRING_H_

#include <stddef.h>
#include <stdint.h>

// STR length
size_t strlen(const char* str);

// iota
// TODO: supercharge the nooby iota
char* iota(int value);

#endif