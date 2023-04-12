includeE4C=./vendor/exceptions4c/
srcE4C=./vendor/exceptions4c/e4c.c

includeCJSON=./vendor/cJSON/
srcCJSON=./vendor/cJSON/cJSON.c

includeApp=./src/
srcApp=./src/*.c

outFile=./bin/AniME.exe

gcc -I $includeE4C -I $includeCJSON -I $includeApp $srcE4C $srcCJSON $srcApp -lcurl -lsqlite3 -o $outFile