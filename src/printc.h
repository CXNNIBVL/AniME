#ifndef PRINTC_H
#define PRINTC_H

#include <stdio.h>
#include <stdarg.h>

#define PRINTC_DEFAULT ""
#define PRINTC_RED     "\x1b[31m"
#define PRINTC_GREEN   "\x1b[32m"
#define PRINTC_YELLOW  "\x1b[33m"
#define PRINTC_BLUE    "\x1b[34m"
#define PRINTC_MAGENTA "\x1b[35m"
#define PRINTC_CYAN    "\x1b[36m"

void printc_clearscreen();
void vprintc(const char* printc_color, const char* fmt, va_list fmt_args);
void printc(const char* printc_color, const char* fmt,...);
void printc_default(const char* fmt, ...);
void printc_red(const char* fmt, ...);
void printc_green(const char* fmt, ...);
void printc_yellow(const char* fmt, ...);
void printc_blue(const char* fmt, ...);
void printc_magenta(const char* fmt, ...);
void printc_cyan(const char* fmt, ...);
void printc_ok(const char* fmt, ...);
void printc_warn(const char* fmt, ...);
void printc_err(const char* fmt, ...);

#endif