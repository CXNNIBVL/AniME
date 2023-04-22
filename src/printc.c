#include "printc.h"

void printc_clearscreen() {
    printf("\e[1;1H\e[2J");
}

void vprintc(const char* printc_color, const char* fmt, va_list fmt_args) {

    const char* PRINTC_RESET = "\x1b[0m";

    printf("%s", printc_color);
    vprintf(fmt, fmt_args);
    printf("%s", PRINTC_RESET);
    fflush(stdout);
}

void printc(const char* printc_color, const char* fmt,...) {

    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(printc_color, fmt, fmt_args);
}

void printc_default(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_DEFAULT, fmt, fmt_args);
}

void printc_red(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_RED, fmt, fmt_args);
}

void printc_green(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_GREEN, fmt, fmt_args);
}

void printc_yellow(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_YELLOW, fmt, fmt_args);
}

void printc_blue(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_BLUE, fmt, fmt_args);
}

void printc_magenta(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_MAGENTA, fmt, fmt_args);
}

void printc_cyan(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_CYAN, fmt, fmt_args);
}

void printc_ok(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_GREEN, fmt, fmt_args);
}

void printc_warn(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_YELLOW, fmt, fmt_args);
}

void printc_err(const char* fmt, ...) {
    va_list fmt_args;
    va_start(fmt_args, fmt);

    vprintc(PRINTC_RED, fmt, fmt_args);
}