#include <util/string.hpp>
#include <term/terminal.hpp>
#include <misc/printf.hpp>

void mirus::printf(const char* args) {
    terminal_writestring(args);
}

void mirus::printf(const int args) {
    terminal_writestring(iota(args));
}