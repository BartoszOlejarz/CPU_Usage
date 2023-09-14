#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "../functions.h"

//global data array definition
float cpu_proc[16];

void *analyzer(){
    //clossing semaphore
    sem_wait(&sem_a);

    //checking if data arrays are not empty
    if(cpu_user[0] == 0 && cpu_sum[0] == 0){
        message = "analyzer.c - Both cpu_user and cpu_sum arrays found empty!";
        terminate_flag = true;
    } else if(cpu_user[0] == 0){
        message = "analyzer.c - cpu_user array found empty!";
        terminate_flag = true;
    } else if(cpu_sum[0] == 0){
        message = "analyzer.c - cpu_sum arrays found empty!";
        terminate_flag = true;
    }

    //setting data array to write to all zeros
    for(int i = 0; i < 16; i++){
       cpu_proc[i] = 0;
    }

    //calculating and writing data to data array
    for(int i = 0; i < 16; i++){
        cpu_proc[i] = ((float)cpu_user[i]/(float)cpu_sum[i])*100;
    }

    //unlocking semaphore and setting alive flag true for watchdog
    sem_post(&sem_p);
    alive_a = true;
    return NULL;
}