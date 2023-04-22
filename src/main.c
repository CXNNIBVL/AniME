#include <stdio.h>
#include <stdlib.h>

#include "printc.h"
#include "jikan.h"
#include "aniutils.h"

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

extern void action_search_anime();
extern void action_view_anime_list();

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
        getVar(NULL, "%d", &action);

        switch (action)
        {
        case 0:
            app_cleanup();
            return 0;
            break;
        case 1:
            action_search_anime();
            break;
        case 2:
            action_view_anime_list();
            break;
        default:
            break;
        }
    }

    return 0;
}