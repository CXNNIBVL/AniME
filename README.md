# AniME
Small MyAnimeList CLI clone written in C. Just a pastime fiddle as a graduation project for my disciples...

# Features

## Search for Anime and Display Anime from API
```json
{
  "data": {
    "mal_id": 0, //internal
    "url": "string",
    "title_english": "string",
    "title": "string",
    "type": "TV",
    "episodes": 0,
    "synopsis": "string",
    "season": "summer",
    "year": 0
  }
}
```
## Save Anime to DB -> Props:
```json
{
    "jikan_api_obj_fields": ...,
    "status": "string", //Currently Watching, Completed, Plan to Watch
    "score": 0, //to 10
    "progress": 0,
}
```
## Display Saved Anime as List (Access DB): 
Rank by CurrentlyWatching->Completed(Score-top-to-bottom)->PlanToWatch

**DISPLAY Color coded** like MyAniList

## Display Saved Anime Details from DB cache

## Edit Saved Anime: 
Change Status, Change Score, Change Progress

## Purge DB 

# Resources:

## [Jikan](https://jikan.moe/) <u>[API](https://docs.api.jikan.moe/#tag/anime)</u>
For Anime data fetching



## <u>[Curl](https://curl.se/libcurl/c/)</u>
- For Web Requests -> API Access and Data fetching
- See documentation and tuts on the official website

<u>[Curl YT Tutorial](https://www.youtube.com/watch?v=daA-KBKfJ_o&t=748s)</u>

<u>[Curl GitBook](https://everything.curl.dev/)</u>

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
## <u>[SqLite Database](https://www.tutorialspoint.com/sqlite/index.htm)</u>

- See docs in linked title

If not installed, run: 
```bash
sudo apt-get install sqlite3
```

And then link against it in the build script with **<u> -lsqlite </u>** :
```bash
gcc -I ... ./src/MyFile.c -lcurl -lsqlite3 -o ...
```

Then use it like:
```c
//MyFile.c

#include <sqlite3.h>

void myfunc(){
    ...
}
```

## [cJSON](https://github.com/DaveGamble/cJSON)
For API Data Parsing

- See docs on the title linked GitHub Page

Include in build script with Include path and source file like:
```bash
gcc -I ./vendor/cJSON/  ./vendor/cJSON/cJSON.c ./src/MyFile.c -lcurl -lsqlite3 -o ...
```

And use it like:
```c
//MyFile.c

#include <cJSON.h>

void myfunc(){
    ...
}
```

## [Colored Terminal output (Stackoverflow)](https://stackoverflow.com/a/3219471)

## Setup

`git clone` the branch "dev-stump" to your local machine. It provides:
- The simple project directory structure
- The app build script `build.sh` 
- A vendor directory with the dependencies for cJSON and e4c
- An install script `install_dependencies.sh` for curl and sqlite3
