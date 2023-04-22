#ifndef CURL_HELPER_H
#define CURL_HELPER_H

#include "curl/curl.h"

struct Response;

struct Response* response_new(size_t write_max_bytes);
void response_free(struct Response* rp);
size_t response_get_total_datalen(const struct Response* rp);
char* response_get_data(const struct Response* rp);

CURLcode curlh_fetch(CURL* curl, struct Response* rp, const char* url);

#endif