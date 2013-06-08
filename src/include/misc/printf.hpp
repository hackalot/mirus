#ifndef _MIRUS_KERNEL_PRINTF_H_
#define _MIRUS_KERNEL_PRINTF_H_

namespace mirus {
    void printf(const char* args);
    void printf(const int args);

    void printc(char args);
}

#endif