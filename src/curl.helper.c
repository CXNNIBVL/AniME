#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "curl.helper.h"

typedef struct Memory {
    char* data;
    size_t len;
} Memory;

typedef struct Response  {
    size_t write_max_bytes;
    struct Memory* chunks;
    size_t count;
} Response;

Response* response_new(size_t write_max_bytes) {
    if(write_max_bytes == 0) return NULL;

    Response* rp = (Response*) malloc(sizeof(Response));

    if(!rp) return NULL;

    *rp = (Response){ .write_max_bytes = write_max_bytes, .chunks = NULL, .count = 0 };
    return rp;
}

void response_free(Response* rp) {
    if(!rp) return;
    free(rp->chunks);
    free(rp);
}

size_t response_get_total_datalen(const Response* rp) {

    if(!rp) { return 0; }
    else if(!(rp->chunks) || rp->count == 0) { return 0; }

    size_t total_len = 0;
    Memory* chunk = rp->chunks;

    while(chunk != rp->chunks + rp->count) {
        total_len += chunk->len;
        chunk++;
    }

    return total_len;
}

static size_t _response_write_data(Response* rp, char* content, size_t len) {

    if(!rp || !content || len == 0) return 0;

    size_t written = 0;
    
    while(written < len) {
        
        size_t data_left = len - written;
        size_t chunk_size = data_left >= rp->write_max_bytes ? rp->write_max_bytes : data_left;
        char* chunk = (char*) malloc( (chunk_size + 1) * sizeof(char));

        if(!chunk) return 0;

        char* content_position = content + written;
        memcpy(chunk, content_position, chunk_size);
        chunk[chunk_size] = '\0';

        Memory* chunks;
        if(!(rp->chunks)) { chunks = (Memory*) malloc(sizeof(Memory)); }
        else { chunks = (Memory*) realloc(rp->chunks, (rp->count + 1) * sizeof(Memory)); }

        if(!chunks) {
            free(chunk);
            return 0;
        }

        chunks[rp->count] = (Memory){ .data = chunk, .len = chunk_size };
        rp->chunks = chunks;
        rp->count++;

        written += chunk_size;
    }
    
    return written;
}

static size_t _curl_write_data(void* content, size_t size, size_t nmemb, void* userp) {
    size_t real_size = size * nmemb;
    Response* rp = (Response*) userp;

    return _response_write_data(rp, (char*) content, real_size);
}

CURLcode curlh_fetch(CURL* curl, Response* rp, const char* url) {

    if(!curl || !rp || !url) return CURLE_OK;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _curl_write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) rp);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.78.0");
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res;
    res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_reset(curl);

    return res;
}

char* response_get_data(const struct Response* rp) {

    if(!rp) return NULL;

    size_t data_len = response_get_total_datalen(rp);
    char* data = (char*) malloc((data_len + 1) * sizeof(char));

    if(!data) return NULL;

    data[data_len] = '\0';
    size_t position = 0;
    Memory* chunk = rp->chunks;
    while(chunk != rp->chunks + rp->count) {
        memcpy(data + position, chunk->data, chunk->len);
        position += chunk->len;
        chunk++;
    }

    return data;
}

