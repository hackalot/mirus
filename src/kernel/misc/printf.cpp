#include <util/string.hpp>
#include <term/terminal.hpp>
#include <misc/printf.hpp>

void mirus::printf(const char* args) {
    mirus::terminal_writestring(args);
}

void mirus::printf(const int args) {
    mirus::terminal_writestring(iota(args));
}