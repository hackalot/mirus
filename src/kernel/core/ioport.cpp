#include <core/ioport.hpp>

unsigned char mirus::inb(unsigned short _port) {
    unsigned char rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void mirus::outb(unsigned short _port, unsigned char _data) {
    asm volatile ("outb %1, %0" : : "dN" (_port), "a" (_data));
}