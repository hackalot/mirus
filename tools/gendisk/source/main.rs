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
// raptordisk - Raptor disk imaging utility
//              Useful for ramdisks, backups, and the like
//
// main.rs    - Entry point
//

use std::os;

fn printUsage() {
    println("raptordisk\n");

    println("USAGE");
    println("\traptordisk [OPTIONS]... [DIRECTORY]...\n");

    println("DESCRIPTION");
    println("\tGenerates disk images from directory structures\n");

    println("OPTIONS");
    println("\t-o, --output");
    println("\t\tspecify output file name (default: filesystem.img)");

    println("\t-c, --compression");
    println("\t\tspecify compression level (default: 0)");

    println("\t-q, --quiet");
    println("\t\tmute output");
}

fn main() {
    let mut outputName = "filesystem.img";
    let mut dirName: ~str;
    let mut compression = 0;
    let mut quiet = false;

    // printUsage();

    let args = os::args();

    for arg_name in args.iter() {
        println(arg_name);
    }
}