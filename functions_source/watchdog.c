#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "../functions.h"

void *watchdog(){
    //main watchdog loop
    while (1){
        //giving threads some time to execute
        sleep(1);
        //checking if functions is dead or if reminate flag is up, if so watchdog ends and termination is processed
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
        //waiting for next loop
        sleep(1);
    }
}