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
// atapio.cpp - ATA PIO mode implimentation
//

#include <stdafx.hpp>
#include <hardware/atapio.hpp>
#include <util/ports.hpp>
#include <util/asm.hpp>
#include <debug/debug.hpp>

// Use ALL THE PORTS!
using mirus::hardware::io::inb;
using mirus::hardware::io::outb;
using mirus::hardware::io::ins;
using mirus::hardware::io::outs;
using mirus::hardware::io::inl;
using mirus::hardware::io::outl;
using mirus::hardware::io::insm;
using mirus::hardware::io::outsm;

namespace mirus
{
    namespace hardware
    {
        ide_channel_registers ide_channels;
        ide_device            ide_devices[4];
        uint8_t               ide_buffer[2048] = {0};
        bool                  ide_irq_invoked = false;
        uint8_t               atapi_packet[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        void detect_ide()
        {

        }

        void ata_io_wait(uint16_t bus)
        {
            inb(bus + (int)ATA::REG_ALTSTATUS);
            inb(bus + (int)ATA::REG_ALTSTATUS);
            inb(bus + (int)ATA::REG_ALTSTATUS);
            inb(bus + (int)ATA::REG_ALTSTATUS);
        }

        int ata_wait(uint16_t bus, int advanced)
        {
            uint8_t status;

            ata_io_wait(bus);

            while ((status = inb(bus + (int)ATA::REG_ALTSTATUS)) & (int)ATA::SR_BSY);

            if (advanced)
            {
                status = inb(bus + (int)ATA::REG_STATUS);

                if (status & (int)ATA::SR_ERR)
                    return 1;
                if (status & (int)ATA::SR_DF)
                    return 1;
                if (!(status & (int)ATA::SR_DRQ))
                    return 1;
            }

            return 0;
        }

        void ata_select(uint16_t bus)
        {
            outb(bus + (int)ATA::REG_HDDEVSEL, 0xA0);
        }

        void ata_wait_ready(uint16_t bus)
        {
            while (inb(bus + (int)ATA::REG_STATUS) & (int)ATA::SR_BSY);
        }

        void ide_install(uint16_t bus)
        {
            debug::debugger::write("[log] Installing IDE device on bus ");
            debug::debugger::write(bus);
            debug::debugger::flush();

            outb(bus + 1, 1);
            outb(bus + 0x306, 0);

            ata_select(bus);
            ata_io_wait(bus);

            outb(bus + (int)ATA::REG_COMMAND, (int)ATA::CMD_IDENTIFY);
            ata_io_wait(bus);

            unsigned int status = inb(bus + (int)ATA::REG_COMMAND);
            debug::debugger::write("[log] status = ");
            debug::debugger::write(status);
            debug::debugger::flush();

            ata_wait_ready(bus);

            ata_identify device;
            uint16_t* buffer = (uint16_t*)&device;

            for (int i = 0; i < 256; ++i)
                buffer[i] = ins(bus);

            uint8_t* ptr = (uint8_t*)&device.model;
            for (int i = 0; i < 39; i += 2)
            {
                uint8_t tmp = ptr[i + 1];
                ptr[i + 1] = ptr[i];
                ptr[i] = tmp;
            }

            debug::debugger::write("[log] ATA device: ");
            debug::debugger::write(device.model);
            debug::debugger::flush();

            debug::debugger::write("[log] sectors_48: ");
            debug::debugger::write((unsigned int)device.sectors_48);
            debug::debugger::flush();

            debug::debugger::write("[log] sectors_28: ");
            debug::debugger::write((unsigned int)device.sectors_28);
            debug::debugger::flush();

            outb(bus + (int)ATA::REG_CONTROL, 0x02);
        }

        void ide_read_sector(uint16_t bus,
            uint8_t slave,
            uint32_t lba,
            uint8_t* buffer)
        {
            int errors = 0;

            outb(bus + (int)ATA::REG_CONTROL, 0x02);
            ata_wait_ready(bus);

            outb(bus + (int)ATA::REG_HDDEVSEL, 0xe0 
                | slave << 4 
                | (lba & 0x0f000000) >> 24);

            outb(bus + (int)ATA::REG_FEATURES, 0x00);
            outb(bus + (int)ATA::REG_SECCOUNT0, 1);
            outb(bus + (int)ATA::REG_LBA0, (lba & 0x000000ff) >> 0);
            outb(bus + (int)ATA::REG_LBA1, (lba & 0x0000ff00) >> 8);
            outb(bus + (int)ATA::REG_LBA2, (lba & 0x00ff0000) >> 16);
            outb(bus + (int)ATA::REG_COMMAND, (int)ATA::CMD_READ_PIO);

            if (ata_wait(bus, 1))
            {
                debug::debugger::write("[error] Error found during read of LBA block ");
                debug::debugger::write((int)lba);
                debug::debugger::flush();

                errors++;

                if (errors > 4)
                {
                    debug::debugger::writeln("[error] Too many errors during block read.");
                    return;
                }
            }

            int size = 256;
            insm(bus, buffer, size);
            ata_wait(bus, 0);
        }

        void ide_write_sector(uint16_t bus,
            uint8_t slave,
            uint32_t lba,
            uint8_t* buffer)
        {
            outb(bus + (int)ATA::REG_CONTROL, 0x02);
            ata_wait_ready(bus);
            outb(bus + (int)ATA::REG_HDDEVSEL, 0xe0 
                | slave << 4 
                | (lba & 0x0f000000) >> 24);

            ata_wait_ready(bus);

            outb(bus, 0);
            outb(bus + (int)ATA::REG_FEATURES, 0x00);
            outb(bus + (int)ATA::REG_SECCOUNT0, 0x01);
            outb(bus + (int)ATA::REG_LBA0, (lba & 0x000000ff) >> 0);
            outb(bus + (int)ATA::REG_LBA1, (lba & 0x0000ff00) >> 8);
            outb(bus + (int)ATA::REG_LBA2, (lba & 0x00ff0000) >> 16);
            outb(bus + (int)ATA::REG_COMMAND, (int)ATA::CMD_WRITE_PIO);

            ata_wait(bus, 0);

            int size = 256;
            outsm(bus, buffer, size);
            outb(bus + 0x07, (int)ATA::CMD_CACHE_FLUSH);
            ata_wait(bus, 0);
        }

        int ide_cmp(uint32_t* ptr1,
            uint32_t* ptr2,
            size_t size)
        {
            // TODO: silly mirus, there is no such thing as assert yet...
            // assert(!(size % 4)); 
            uint32_t i = 0;
            
            while (i < size)
            {
                if (*ptr1 != *ptr2)
                    return 1;
                
                ptr1++;
                ptr2++;
                i += 4;
            }

            return 0;
        }

        void ide_write_sector_retry(uint16_t bus,
            uint8_t slave,
            uint32_t lba,
            uint8_t* buffer)
        {

        }
    } // !namespace
} // !namespace