#include <stdlib.h>

#include "printc.h"
#include "aniutils.h"
#include "jikan.h"

#include <unistd.h>

static void get_query(char* buffer, size_t buffer_size) {

    if(!buffer) {
        return;
    }

    printc_cyan("Anime Search:\n=============\n");

    printc_cyan("Search by title: ");
    getLine(NULL, buffer, buffer_size);
}

void action_search_anime() {

    printc_clearscreen();
    
    char query[100] = "";
    get_query(query, sizeof(query));
    
    //TODO: Give Query String to JIKAN API
    // Receive API Object

    int err;
    JikanAnimeSearchResult* sr = jikan_search_anime(query, JikanSearchOpts_DefaultPage, JikanSearchOpts_DefaultLimit, &err);

    if(err) printc_err("%s\n", jikan_get_error());

    for(int i = 0; i < sr->anime_count; i++) {
        
    }

    jikan_search_result_free(sr);

    sleep(10);
}