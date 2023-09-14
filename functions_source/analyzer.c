#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "../functions.h"

float cpu_proc[16];

void *analyzer(){
    sem_wait(&sem_a);

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

    for(int i = 0; i < 16; i++){
       cpu_proc[i] = 0;
    }

    for(int i = 0; i < 16; i++){
        cpu_proc[i] = ((float)cpu_user[i]/(float)cpu_sum[i])*100;
    }

    sem_post(&sem_p);
    alive_a = true;
};