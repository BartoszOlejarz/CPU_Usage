#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "../functions.h"

float cpu_proc[16];

void *analyzer(){
    sem_wait(&sem_a);

    for(int i = 0; i < 16; i++){
       cpu_proc[i] = 0;
    }

    for(int i = 0; i < 16; i++){
        cpu_proc[i] = ((float)cpu_user[i]/(float)cpu_sum[i])*100;
    }

    sem_post(&sem_p);
};