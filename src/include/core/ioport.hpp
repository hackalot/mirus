#ifndef _MIRUS_KERNEL_IOPORT_H_
#define _MIRUS_KERNEL_IOPORT_H_

namespace mirus {
    //inb
    unsigned char inb (unsigned short _port);

    // outb
    void outb (unsigned short _port, unsigned char _data);
}

#endif