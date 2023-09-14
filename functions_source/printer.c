#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "../functions.h"

void *printer(){
    sem_wait(&sem_p);
    
    if(cpu_proc[0] == 0.0){
        message = "printer.c - cpu_proc array found empty!";
        terminate_flag = true;
    }

    printf("\n------------------------------");
    for(int i = 0; i < 16 ; i++){
        printf("\nCPU%d: %7.2lf%%", i, cpu_proc[i]);
    }
    printf("\n------------------------------");

    sem_post(&sem_r);
    
    alive_p = true;           
};