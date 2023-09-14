#include <stdio.h>
#include <time.h>

#include "../functions.h"

void *logger(){
    //opening log.txt file to write
    FILE *pLog = fopen("log.txt", "a");

    //checking if log.txt was oppened correctly
    if (pLog != NULL) {
        //setting up time data structs
        time_t rawtime;
        struct tm *timeinfo;

        //geint raw time form system and making it more readable for human with localtime()
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        //setting size of time buffor
        char timeBuffor[80];

        //setting time and date to write into log.txt
        strftime(timeBuffor, sizeof(timeBuffor), "<%d-%m-%Y %H:%M:%S> :: ", timeinfo);

        //writing log message with date and time into new line of log.txt
        fprintf(pLog, "%s%s\n", timeBuffor, message);
        
        // clossing file
        fclose(pLog);
    }
    return NULL;
}