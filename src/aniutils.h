#ifndef ANIUTILS_H
#define ANIUTILS_H

#include <stddef.h>

#define SIZEOF_ARR(arr) sizeof(arr) / sizeof(arr[0])

void clear_string(char* str, size_t len);
char* clone_string(const char* str, size_t len);
int getLine (const char *prmpt, char *buff, size_t sz);
void getVar(const char* prompt, const char* fmt, ...);


#endif