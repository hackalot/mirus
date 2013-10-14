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
// main.cpp - Entry point
//

#include <rfsdisk.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>
#include <dirent.h>
#include <stdio.h>

std::string output_name = "filesystem.img";
std::string input_dir;

enum class raptor_inode_type : int
{
    null = 0x00,
    file = 0x01,
    pipe = 0x02,
    dir  = 0x03
};

enum class raptor_inode_flags : int
{
    ro         = 0x00,
    hidden     = 0x01,
    compressed = 0x02,
    encrypted  = 0x03
};

class raptor_inode
{
public:
    char name[256];
    uint8_t   type;
    uint8_t   flags;
    uint8_t   permissions;
    uintptr_t blocks[256];
};

class raptor_block
{
public:
    uint32_t data[512];
};

class raptor_superblock
{
public:
    int32_t fs_magic;
    uint8_t fs_version;
    uint8_t fs_class;
    uint32_t inode_count;
    uint32_t used_inode_count;
    uint32_t used_block_count;
};

void print_usage()
{
    std::cout << "rfsdisk\n" << std::endl;

    std::cout << "USAGE" << std::endl;
    std::cout << "\trfsdisk [OPTIONS]... [DIRECTORY]...\n" << std::endl;

    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tGenerates disk images from directory structures\n" << std::endl;

    std::cout << "OPTIONS" << std::endl;
    std::cout << "\t-o, --output" << std::endl;
    std::cout << "\t\tspecify output file name (default: filesystem.img)" << std::endl;
}

void generate_image()
{
    raptor_superblock mBlock;
    mBlock.fs_magic = 0x2a2a2a2a;
    mBlock.fs_version = 1;
    mBlock.fs_class = 2;



    FILE* outfile;

    outfile = fopen(output_name.c_str(), "wb");

    if (!outfile)
    {
        printf("Can't open file.");
        exit(1);
    }

    fwrite(&mBlock, sizeof(raptor_superblock), 1, outfile);
    fclose(outfile);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
        exit(1);
    }

    if (argv[1])
        output_name = argv[1];

    if (argv[2])
        input_dir = argv[2];
    else
    {
        std::cout << "Error.  Must provide input directory name" << std::endl;
        exit(1);
    }

    generate_image();

    return 0;
}