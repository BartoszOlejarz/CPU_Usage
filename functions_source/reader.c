#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "../functions.h"

//data arrays and defined
int cpu_user[16];
int cpu_sum[16];

void *reader(){
    //semaphore close
    sem_wait(&sem_r);

    //setting size of reading buffer
    char buffer[255];

    //opening /proc/stat file read
    FILE *pFile;
    pFile = fopen("/proc/stat", "r");

    //checking if file was opened correctly or found empty, if not file will closed and termination flag will be set up 
    if(pFile == NULL){
        message = "reader.c - Can't open /proc/stat or found empty!";
        fclose(pFile);
        terminate_flag = true;
    } 

    //geting firs line of file, and skiping it
    fgets(buffer, sizeof(buffer), pFile);
    
    //setting while data arrays to be full of zeros, to avoid errors
    for(int i = 0; i < 16; i++){
        cpu_user[i] = 0;
        cpu_sum[i] = 0;
    }
    
    //geting lines form file, form 2 do 17 (for 16 cores), and searching for decimal nambers, if number is found calculations are made
    for(int i = 0; i < 16 ; i++){
        int temp = 0;
        fgets(buffer, sizeof(buffer), pFile);
        sscanf(buffer, "%*s %d", &cpu_user[i]);
        char *token = strtok(buffer, " ");
        while(token != NULL){
            if (sscanf(token, "%d", &temp) == 1){
                cpu_sum[i] += temp;
            }
        token = strtok(NULL, " ");
        }
    }

    //closing file, unlocking semaphore and setting alive flag up for watchdog
    fclose(pFile);
    sem_post(&sem_a);
    alive_r = true;
    return NULL;
}