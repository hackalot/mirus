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

#ifndef _MIRUS_KERNEL_UTIL_STRING_H_
#define _MIRUS_KERNEL_UTIL_STRING_H_

#include <stddef.h>
#include <stdint.h>

#include <mem/memory.hpp>

// TODO: add more useful functions
// TODO: move under mirus namespace
// TODO: mirus::util

// STR length
size_t strlen(const char *str);

// iota
// TODO: supercharge the nooby iota
char *iota(int value);

// pad
char* strpad(char* data, int padlen);

// strcpy
// char* strcpy(char* dest, const char* src);

// strcat
char* strcat(char* dest, const char* src);

#endif
