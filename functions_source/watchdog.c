#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "../functions.h"

void *watchdog(){
    while (1){
        sleep(1);

        if(!alive_r){
            printf("\nReader found dead!");
            message = "watchdog.c - Reader found dead!";
            terminate_flag = true;
            pthread_exit(NULL);
        } else if (!alive_a){
            printf("\nAnalyzer found dead!");
            message = "watchdog.c - Analyzer found dead!";
            terminate_flag = true;
            pthread_exit(NULL);
        } else if (!alive_p){
            printf("\nPrinter found dead!");
            message = "watchdog.c - Printer found dead!";
            terminate_flag = true;
            pthread_exit(NULL);
        } else if (terminate_flag == true){
           pthread_exit(NULL);
        }
        sleep(1);
    }
}