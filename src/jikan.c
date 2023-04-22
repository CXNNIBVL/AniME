#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "curl/curl.h"

#include "jikan.h"
#include "aniutils.h"
#include "curl.helper.h"
#include "cJSON.h"

void odbg(const char* label) {
    printf("%s\n", label);
    fflush(stdout);
}

#define JIKAN_RESPONSE_CHUNK_WRITE_MAX_BYTES 1000

static const char* API_ROOT = "https://api.jikan.moe/v4/anime";

static const char* API_ERROR_MESSAGE = NULL;
static CURL* curl;

static void _set_error(const char* message) {
    API_ERROR_MESSAGE = message;
}

static void _set_error_curl(CURLcode err) {
    const char* curl_err = curl_easy_strerror(err);
    _set_error(curl_err);
}

const char* jikan_get_error() {
    return API_ERROR_MESSAGE;
}

JikanInitError jikan_init() {
    
    curl = curl_easy_init();

    if(!curl) {
        _set_error("Unable to initialise CURL");
        return JikanInitError_CurlInitFailed;
    }

    return JikanInitError_None;
}

void jikan_cleanup() {
    curl_easy_cleanup(curl);
}

static void _init_anime(JikanAnime* anime, int mal_id,
        const char* url, const char* title_english, 
        const char* title, const char* type, 
        int episodes, const char* synopsis, 
        const char* season, int year
) {
    anime->mal_id = mal_id;
    anime->url = url ? clone_string(url, strlen(url)) : NULL;
    anime->title_english = title_english ? clone_string(title_english, strlen(title_english)) : NULL;
    anime->title = title ? clone_string(title, strlen(title)) : NULL;
    anime->type = type ? clone_string(type, strlen(type)) : NULL;
    anime->episodes = episodes;
    anime->synopsis = synopsis ? clone_string(synopsis, strlen(synopsis)) : NULL;
    anime->season = season ? clone_string(season, strlen(season)) : NULL;
    anime->year = year;
}

static JikanAnime* _new_anime(
        int mal_id,
        const char* url,
        const char* title_english,
        const char* title,
        const char* type,
        int episodes,
        const char* synopsis,
        const char* season,
        int year
) {

    JikanAnime* anime = (JikanAnime*) malloc(sizeof(JikanAnime));

    if(!anime) return NULL;
    
    _init_anime(anime, mal_id, url, title_english, title, type, episodes, synopsis, season, year);

    return anime;
}

void jikan_free_anime(JikanAnime* anime) {

    if(!anime) return;

    free(anime->url);
    free(anime->title_english);
    free(anime->title);
    free(anime->type);
    free(anime->synopsis);
    free(anime->season);
    free(anime);
}

static JikanAnimeSearchResult* _search_result_new(int anime_count, int current_page, int has_next_page) {
    JikanAnimeSearchResult* sr = (JikanAnimeSearchResult*) malloc(sizeof(JikanAnimeSearchResult));
    if(!sr) return NULL;

    JikanAnime* anime = (JikanAnime*) malloc(anime_count * sizeof(JikanAnime));
    if(!anime) {
        jikan_search_result_free(sr);
        return NULL;    
    }

    *sr = (JikanAnimeSearchResult){ .anime = anime, .anime_count = anime_count, .current_page = current_page, .has_next_page = has_next_page };
    return sr;
}

void jikan_search_result_free(JikanAnimeSearchResult* result) {

    if(!result) return;

    if(result->anime) { free(result->anime); }

    free(result);
}

const char* get_curl_err(CURLcode err) {
    const char* str = curl_easy_strerror(err);
    return str;
}

void display_curl_err(CURLUcode err) {
    const char* str = get_curl_err(err);   
    printf("CURL ERR: %s\n", str);
}

static int _search_anime_construct_url(char* buffer, const char* query, int page, int limit) {

    if(!buffer) return 1;

    if(page < 1) page = 1;
    if(limit < 1) limit = 25;
    if(!query) query = "";

    char* url_encoded_query = curl_easy_escape(curl, query, strlen(query));

    if(!url_encoded_query) {
        _set_error("Out of memory.");
        return 1;
    }

    sprintf(buffer, "%s?q=%s&page=%d&limit=%d", API_ROOT, url_encoded_query, page, limit);
    curl_free(url_encoded_query);

    return 0;
}

static JikanAnimeSearchResult* _parse_search_result(const char* json, int* err) {

    if(!json) {
        if(err) *err = 1;
        _set_error("Json was null.");
        return NULL;
    }

    cJSON* root = cJSON_Parse(json);
    if(!root) {
        if(err) *err = 1;
        _set_error("Invalid json.");
        return NULL;
    }

    cJSON* pagination = cJSON_GetObjectItemCaseSensitive(root, "pagination");

    int has_next_page = cJSON_GetObjectItemCaseSensitive(pagination, "has_next_page")->valueint;
    int current_page = cJSON_GetObjectItemCaseSensitive(pagination, "current_page")->valueint;
    cJSON* items = cJSON_GetObjectItemCaseSensitive(pagination, "items");
    int anime_count = cJSON_GetObjectItemCaseSensitive(items, "count")->valueint;

    JikanAnimeSearchResult* sr = _search_result_new(anime_count, current_page, has_next_page);
    if(!sr) {
        cJSON_free(root);
        if(err) *err = 1;
        _set_error("Out of memory.");
        return NULL;
    }

    if(sr->anime_count == 0) {
        sr->anime = NULL;
        cJSON_free(root);
        if(err) *err = 0;
        return sr;
    }

    cJSON* data = cJSON_GetObjectItemCaseSensitive(root, "data");
    cJSON* anime_json = NULL;
    int i = 0;
    cJSON_ArrayForEach(anime_json, data) {

        int mal_id = cJSON_GetObjectItemCaseSensitive(anime_json, "mal_id")->valueint;
        const char* url = cJSON_GetObjectItemCaseSensitive(anime_json, "url")->valuestring;
        const char* title = cJSON_GetObjectItemCaseSensitive(anime_json, "title")->valuestring;
        const char* title_english = cJSON_GetObjectItemCaseSensitive(anime_json, "title_english")->valuestring;
        const char* type = cJSON_GetObjectItemCaseSensitive(anime_json, "type")->valuestring;
        int episodes = cJSON_GetObjectItemCaseSensitive(anime_json, "episodes")->valueint;
        const char* synopsis = cJSON_GetObjectItemCaseSensitive(anime_json, "synopsis")->valuestring;
        const char* season = cJSON_GetObjectItemCaseSensitive(anime_json, "season")->valuestring;
        int year = cJSON_GetObjectItemCaseSensitive(anime_json, "year")->valueint;

        JikanAnime* anime = sr->anime + i;
        _init_anime(anime, mal_id, url, title_english, title, type, episodes, synopsis, season, year);
        i++;
    }

    cJSON_free(root);
    
    if(err) *err = 0;
    return sr;
}

JikanAnimeSearchResult* jikan_search_anime(const char* query, int page, int limit, int* err) {

    char url[300] = "";
    if(_search_anime_construct_url(url, query, page, limit)) {
        _set_error("Unable to construct query URL.");
        if(err) *err = 1;
        return NULL;
    }

    struct Response* rp = response_new(JIKAN_RESPONSE_CHUNK_WRITE_MAX_BYTES);

    if(!rp) {
        if(err) *err = 1;
        _set_error("Out of memory.");
        return NULL;
    }

    CURLcode res;
    res = curlh_fetch(curl, rp, url);

    if(res) {
        curl_easy_reset(curl);
        response_free(rp);
        if(err) *err = 1;

        _set_error_curl(res);
        return NULL;
    }

    curl_easy_reset(curl);

    char* data = response_get_data(rp);
    size_t data_len = response_get_total_datalen(rp);

    if(!data || data_len == 0) {
        response_free(rp);
        if(err) *err = 1;

        _set_error("Out of memory.");
        return NULL;
    }

    response_free(rp);

    int parse_err = 0;
    JikanAnimeSearchResult* sr = _parse_search_result(data, &parse_err);

    if(!sr || parse_err) {
        if(err) *err = 1;
        free(data);
        return NULL;
    }

    free(data);

    if(err) *err = 0;

    return sr;
}


