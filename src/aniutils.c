#include "aniutils.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void clear_string(char* str, size_t len) {
    if(str) {
        memset(str, 0, len);
    }
}

char* clone_string(const char* str, size_t len) {

    if(!str) return NULL;

    char* cloned = (char*) malloc((len + 1) * sizeof(char));
    memcpy(cloned, str, len); cloned[len] = '\0';

    return cloned;
}

int getLine (const char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return 1;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? 2 : 0;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return 0;
}

void getVar(const char* prompt, const char* fmt, ...) {

    va_list fmt_args;
    va_start(fmt_args, fmt);

    char buf[255];
    getLine(prompt, buf, sizeof(buf));
    vsscanf(buf, fmt, fmt_args);
}