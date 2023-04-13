#include <stdio.h>
#include <stdlib.h>

#include "printc.h"
#include "jikan.h"

int app_init() {

    if(jikan_init()) {
        const char* err = jikan_get_error();
        printc_err("%s\n",err);
        return 1;
    }

    return 0;
}

void app_cleanup() {

    jikan_cleanup();

}

void print_actions() {

    const char* actions =
        "Actions:\n"
        "==========\n"
        "Quit:\t0\n"
        "Search for Anime:\t1\n"
        "View AniME List:\t2\n";

    printc_cyan("%s", actions);
}

int main() {

    printc_clearscreen();

    if(app_init()) {
        app_cleanup();
        return -1;
    }

    while(1) {
        
        printc_clearscreen();
        print_actions();

        int action = 69;
        scanf("%d", &action);

        switch (action)
        {
        case 0:
            app_cleanup();
            return 0;
            break;
        case 1:
            //search for anime
            break;
        case 2:
            //view anime list
            break;
        default:
            break;
        }

    }

    return 0;
}