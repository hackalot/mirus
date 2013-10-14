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

std::string output_name = "filesystem.img";
std::string input_dir;

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
    DIR *dir;
    struct dirent *ent;
    
    if ((dir = opendir(input_dir))) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }
        
        closedir(dir);
    } 
    else 
    {
        exit(1);
    }
}

int main(int argc, char* argv[])
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
        exit(1)
    }

    generate_image();

    return 0;
}