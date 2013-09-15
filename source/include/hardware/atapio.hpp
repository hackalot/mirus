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
// atapio.hpp - ATA PIO mode implimentation
//

#pragma once

namespace mirus
{
    namespace hardware
    {
        //
        // ATA_commands - convinent way to access ATA commands
        //
        enum class ATA_commands : unsigned int
        {
            ATA_SR_BSY                  = 0x80
            ATA_SR_DRDY                 = 0x40
            ATA_SR_DF                   = 0x20
            ATA_SR_DSC                  = 0x10
            ATA_SR_DRQ                  = 0x08
            ATA_SR_CORR                 = 0x04
            ATA_SR_IDX                  = 0x02
            ATA_SR_ERR                  = 0x01

            ATA_ER_BBK                  = 0x80
            ATA_ER_UNC                  = 0x40
            ATA_ER_MC                   = 0x20
            ATA_ER_IDNF                 = 0x10
            ATA_ER_MCR                  = 0x08
            ATA_ER_ABRT                 = 0x04
            ATA_ER_TK0NF                = 0x02
            ATA_ER_AMNF                 = 0x01

            ATA_CMD_READ_PIO            = 0x20
            ATA_CMD_READ_PIO_EXT        = 0x24
            ATA_CMD_READ_DMA            = 0xC8
            ATA_CMD_READ_DMA_EXT        = 0x25
            ATA_CMD_WRITE_PIO           = 0x30
            ATA_CMD_WRITE_PIO_EXT       = 0x34
            ATA_CMD_WRITE_DMA           = 0xCA
            ATA_CMD_WRITE_DMA_EXT       = 0x35
            ATA_CMD_CACHE_FLUSH         = 0xE7
            ATA_CMD_CACHE_FLUSH_EXT     = 0xEA
            ATA_CMD_PACKET              = 0xA0
            ATA_CMD_IDENTIFY_PACKET     = 0xA1
            ATA_CMD_IDENTIFY            = 0xEC

            ATAPI_CMD_READ              = 0xA8
            ATAPI_CMD_EJECT             = 0x1B

            ATA_IDENT_DEVICETYPE        = 0
            ATA_IDENT_CYLINDERS         = 2
            ATA_IDENT_HEADS             = 6
            ATA_IDENT_SECTORS           = 12
            ATA_IDENT_SERIAL            = 20
            ATA_IDENT_MODEL             = 54
            ATA_IDENT_CAPABILITIES      = 98
            ATA_IDENT_FIELDVALID        = 106
            ATA_IDENT_MAX_LBA           = 120
            ATA_IDENT_COMMANDSETS       = 164
            ATA_IDENT_MAX_LBA_EXT       = 200

            IDE_ATA                     = 0x00
            IDE_ATAPI                   = 0x01
 
            ATA_MASTER                  = 0x00
            ATA_SLAVE                   = 0x01

            ATA_REG_DATA                = 0x00
            ATA_REG_ERROR               = 0x01
            ATA_REG_FEATURES            = 0x01
            ATA_REG_SECCOUNT0           = 0x02
            ATA_REG_LBA0                = 0x03
            ATA_REG_LBA1                = 0x04
            ATA_REG_LBA2                = 0x05
            ATA_REG_HDDEVSEL            = 0x06
            ATA_REG_COMMAND             = 0x07
            ATA_REG_STATUS              = 0x07
            ATA_REG_SECCOUNT1           = 0x08
            ATA_REG_LBA3                = 0x09
            ATA_REG_LBA4                = 0x0A
            ATA_REG_LBA5                = 0x0B
            ATA_REG_CONTROL             = 0x0C
            ATA_REG_ALTSTATUS           = 0x0C
            ATA_REG_DEVADDRESS          = 0x0D

            ATA_PRIMARY                 = 0x00
            ATA_SECONDARY               = 0x01

            ATA_READ                    = 0x00
            ATA_WRITE                   = 0x01
        };

        //
        // ide_channel/_registers - hold the status of IDE channel
        //                          registers
        //
        class ide_channel_registers
        {
        public:
            uint16_t base;
            uint16_t ctrl;
            uint16_t bmide;
            uint16_t nein;
        };

        //
        // ide_device - defines a physical IDE hard drive
        //
        class ide_device
        {
        public:
            uint8_t  reserved;
            uint8_t  channel;
            uint8_t  drive;
            uint8_t  type;
            uint8_t  signature;
            uint8_t  capabilities;
            uint32_t command_sets;
            uint32_t size;
            uint8_t  model[41];
        };

        //
        // partition - simple structure to define a disk
        //             partition
        //
        class partition
        {
        public:
            uint8_t  status;
            uint8_t  chs_first_sector[3];
            uint8_t  type;
            uint8_t  chs_last_sector[3];
            uint32_t lba_first_sector;
            uint32_t sector_count;
        };

        //
        // ata_identify - hold ATA device information
        //
        class ata_identify
        {
        public:
            uint16_t flags;
            uint16_t unused1[9];
            char     serial[20];
            uint16_t unused2[3];
            char     firmware[8];
            char     model[40];
            uint16_t sectors_per_int;
            uint16_t unused3;
            uint16_t capabilities[2];
            uint16_t unused4[2];
            uint16_t valid_ext_data;
            uint16_t unused5[5];
            uint16_t size_of_rw_mult;
            uint32_t sectors_28;
            uint16_t unused6[38];
            uint64_t sectors_48;
            uint16_t unused7[152];
        } __attribute__((packed));

        //
        // mbr - defines a master boot record
        //
        class mbr
        {
        public:
            uint8_t   bootstrap[446];
            partition partitions[4];
            uint8_t   signature[2];
        } __attribute__((packed));
    } // !namespace
} // !namespace