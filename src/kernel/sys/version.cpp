// Copyright (c) 2013 Joshua Beitler, Mirus contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <sys/version.hpp>

mirus::version::_kname = "mirus";
mirus::version::_vpost = "dev";
mirus::version::_vcode = "fayette";

mirus::version::_major = BUILD_MAJOR;
mirus::version::_minor = BUILD_MINOR;
mirus::version::_build = BUILD_NUM;

static const char* mirus::version::getKernelName() {
    return mirus::version::_kname;
}

static const char* mirus::version::getVersionString() {
    return mirus::version::_kname 
        + "-" 
        + mirus::version::_major
        + "." 
        + mirus::version::_minor
        + "-"
        + mirus::version::_vpost;
}

static const char* mirus::version::getVersionPostfix() {
    return mirus::version::_vpost;
}

static const char* mirus::version::getVersionCodename() {
    return mirus::version::_vcode;
}

static int mirus::version::getMajor() {
    return mirus::version::_major;
}

static int mirus::version::getMinor() {
    return mirus::version::_minor;
}

static int mirus::version::getBuild() {
    return mirus::version::_build;
}