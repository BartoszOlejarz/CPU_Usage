#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "../functions.h"

void *printer(){
    //clossing semaphore
    sem_wait(&sem_p);
    
    //checking if data array is not empty
    if(cpu_proc[0] == 0.0){
        message = "printer.c - cpu_proc array found empty!";
        terminate_flag = true;
    }

    //printing all data form array to terminal window
    printf("\n------------------------------");
    for(int i = 0; i < 16 ; i++){
        printf("\nCPU%d: %7.2lf%%", i, cpu_proc[i]);
    }
    printf("\n------------------------------");

    //unlocking semaphore and setting alive flag up for watchdog
    sem_post(&sem_r);
    alive_p = true; 
    return NULL;          
}