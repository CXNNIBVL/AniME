# AniME Project

## Features

### Search for Anime and Display Anime from API
```json
{
  "data": {
    "mal_id": 0, //internal
    "url": "string",
    "title_english": "string",
    "title_japanese": "string",
    "type": "TV",
    "episodes": 0,
    "synopsis": "string",
    "season": "summer",
    "year": 0
  }
}
```
### Save Anime to DB -> Props:
```json
{
    "status": "string", //Currently Watching, Completed, Plan to Watch
    "score": 0, //to 10
    "progress": 0,
    //...api_obj_fields,
}
```
### Display Saved Anime as List (Access DB): 
Rank by CurrentlyWatching->Completed(Score-top-to-bottom)->PlanToWatch

**DISPLAY Color coded** like MyAniList

### Display Saved Anime Details from DB cache

### Edit Saved Anime: 
Change Status, Change Score, Change Progress

### Purge DB 

## Resources:

### [Jikan](https://jikan.moe/) <u>[API](https://docs.api.jikan.moe/#tag/anime)</u>
For Anime details fetching



### <u>[Curl](https://curl.se/libcurl/c/)</u>
For Web Requests -> API Access and Data fetching

<u>[Curl Tutorial](https://www.youtube.com/watch?v=daA-KBKfJ_o&t=748s)</u>

Use in:
```c
//MyFile.c
#include <curl/curl.h>

void myfunc(){
    ...
}

```
And: <u>**-lcurl**</u> flag in build script
```bash
gcc -I ... ./src/MyFile.c -lcurl -o ...
```
### <u>[SqLite Database](https://www.sqlite.org/cintro.html)</u>