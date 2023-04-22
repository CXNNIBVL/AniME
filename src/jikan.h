#ifndef API_H
#define API_H

    typedef enum JikanInitError {
        JikanInitError_None = 0,
        JikanInitError_CurlInitFailed = 1,
    } JikanInitError;

    /*
        Initializes the API

        @return JikanInitError
    */
    JikanInitError jikan_init();

    /*
        API Cleanup
    */
    void jikan_cleanup();

    /*
        Used to get the current API Error message.
    */
    const char* jikan_get_error();

    typedef struct JikanAnime {
        int mal_id;
        char* url;
        char* title_english;
        char* title;
        char* type;
        int episodes;
        char* synopsis;
        char* season;
        int year;
    } JikanAnime;

    typedef struct JikanAnimeSearchResult {
        JikanAnime* anime;
        int anime_count;
        int current_page;
        int has_next_page;
    } JikanAnimeSearchResult;

    typedef enum JikanSearchOpts {
        JikanSearchOpts_DefaultPage = 0,
        JikanSearchOpts_DefaultLimit = -1
    } JikanSearchOpts;

    // Queries Jikan API for a loose Anime match by the query string
    //
    // @param query The Anime title; Will not be owned.
    // @param page  The MAL page; for page < 1 -> 1 by default; Pass JikanSearchOpts_DefaultPage for default
    // @param limit The max. amount of results returned in query; For limit <  1 -> 25 by default; Pass JikanSearchOpts_DefaultLimit for default
    // @param err   Will be set to 1 if an error occurred, 0 otherwise. Err can be queried by calling jikan_get_error(). 
    //
    // @returns pointer to a search result. Must be freed with jikan_anime_search_result_free()
    JikanAnimeSearchResult* jikan_search_anime(const char* query, int page, int limit, int* err);


    // Free a JikanAnime
    void jikan_free_anime(JikanAnime* anime);

    // Free a Jikan Search Result
    void jikan_search_result_free(JikanAnimeSearchResult* result);

#endif