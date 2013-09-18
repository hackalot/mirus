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
// pio.hpp - (PATA) PIO
//

#pragma once

namespace mirus
{
	namespace hardware
	{
		//
		// ata_commands - All ATA command operations we will ever need
		//
		enum class ata_commands : unsigned int
		{
			SR_BSY                  = 0x80,
            SR_DRDY                 = 0x40,
            SR_DF                   = 0x20,
            SR_DSC                  = 0x10,
            SR_DRQ                  = 0x08,
            SR_CORR                 = 0x04,
            SR_IDX                  = 0x02,
            SR_ERR                  = 0x01,

            ER_BBK                  = 0x80,
            ER_UNC                  = 0x40,
            ER_MC                   = 0x20,
            ER_IDNF                 = 0x10,
            ER_MCR                  = 0x08,
            ER_ABRT                 = 0x04,
            ER_TK0NF                = 0x02,
            ER_AMNF                 = 0x01,

            CMD_READ_PIO            = 0x20,
            CMD_READ_PIO_EXT        = 0x24,
            CMD_READ_DMA            = 0xC8,
            CMD_READ_DMA_EXT        = 0x25,
            CMD_WRITE_PIO           = 0x30,
            CMD_WRITE_PIO_EXT       = 0x34,
            CMD_WRITE_DMA           = 0xCA,
            CMD_WRITE_DMA_EXT       = 0x35,
            CMD_CACHE_FLUSH         = 0xE7,
            CMD_CACHE_FLUSH_EXT     = 0xEA,
            CMD_PACKET              = 0xA0,
            CMD_IDENTIFY_PACKET     = 0xA1,
            CMD_IDENTIFY            = 0xEC,

            ATAPI_CMD_READ          = 0xA8,
            ATAPI_CMD_EJECT         = 0x1B,

            IDENT_DEVICETYPE        = 0,
            IDENT_CYLINDERS         = 2,
            IDENT_HEADS             = 6,
            IDENT_SECTORS           = 12,
            IDENT_SERIAL            = 20,
            IDENT_MODEL             = 54,
            IDENT_CAPABILITIES      = 98,
            IDENT_FIELDVALID        = 106,
            IDENT_MAX_LBA           = 120,
            IDENT_COMMANDSETS       = 164,
            IDENT_MAX_LBA_EXT       = 200,

            IDE_ATA                 = 0x00,
            IDE_ATAPI               = 0x01,
 
            MASTER                  = 0x00,
            SLAVE                   = 0x01,

            REG_DATA                = 0x00,
            REG_ERROR               = 0x01,
            REG_FEATURES            = 0x01,
            REG_SECCOUNT0           = 0x02,
            REG_LBA0                = 0x03,
            REG_LBA1                = 0x04,
            REG_LBA2                = 0x05,
            REG_HDDEVSEL            = 0x06,
            REG_COMMAND             = 0x07,
            REG_STATUS              = 0x07,
            REG_SECCOUNT1           = 0x08,
            REG_LBA3                = 0x09,
            REG_LBA4                = 0x0A,
            REG_LBA5                = 0x0B,
            REG_CONTROL             = 0x0C,
            REG_ALTSTATUS           = 0x0C,
            REG_DEVADDRESS          = 0x0D,

            PRIMARY                 = 0x00,
            SECONDARY               = 0x01,

            READ                    = 0x00,
            WRITE                   = 0x01
		};

		//
		// ata_status - ATA status codes
        //
		enum class ata_status : unsigned int
		{
            None                    = 0x00,
            Busy                    = 0x80,
            ATA_SR_DRD              = 0x40,
            ATA_SR_DF               = 0x20,
            ATA_SR_DSC              = 0x10,
            DRQ                     = 0x08,
            ATA_SR_COR              = 0x04,
            ATA_SR_IDX              = 0x02,
            Error                   = 0x01
		};

        //
        // ata_error - ATA error codes
        //
        enum class ata_error : unsigned int
        {
            ATA_ER_BBK              = 0x80,
            ATA_ER_UNC              = 0x40,
            ATA_ER_MC               = 0x20,
            ATA_ER_IDNF             = 0x10,
            ATA_ER_MCR              = 0x08,
            ATA_ER_ABRT             = 0x04,
            ATA_ER_TK0NF            = 0x02,
            ATA_ER_AMNF             = 0x01
        };

		// PIO - ATA PIO methods
		class PIO
		{
		public:
			void install(uint32_t bus);

			// rw
			void read_sector(unsigned int lba);
			void write_sector(unsigned int lba);

			// misc
			void ata_wait();
			void ata_reset();
		};

		//
        // ide_channel_registers - hold the status of IDE channel
        //                         registers
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