#include <stdio.h>
#include <time.h>

#include "../functions.h"

void *logger(){

    FILE *pLog = fopen("log.txt", "a");
    if (pLog != NULL) {
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        char timeBuffor[80];
        strftime(timeBuffor, sizeof(timeBuffor), "<%d-%m-%Y %H:%M:%S> :: ", timeinfo);

        fprintf(pLog, "%s%s\n", timeBuffor, message);
        fclose(pLog);
    }
}