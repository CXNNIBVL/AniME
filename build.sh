includeCJSON=./vendor/cJSON/
srcCJSON=./vendor/cJSON/cJSON.c

includeApp=./src/
srcApp=./src/*.c

outFile=./bin/AniME.exe

gcc -I $includeCJSON -I $includeApp $srcCJSON $srcApp -lcurl -lsqlite3 -o $outFile