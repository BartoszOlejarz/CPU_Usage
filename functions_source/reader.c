#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include "../functions.h"

int cpu_user[16];
int cpu_sum[16];

void *reader(){
    sem_wait(&sem_r);
    char buffer[255];

    FILE *pFile;
    pFile = fopen("/proc/stat", "r");
    fgets(buffer, sizeof(buffer), pFile); //discarding 1st line of /proc/stat

    for(int i = 0; i < 16; i++){
        cpu_user[i] = 0;
        cpu_sum[i] = 0;
    }

    for(int i = 0; i < 16 ; i++){ //reading lines form 2 do 17 (for 16 cpu cores)
        int temp = 0;  //setting temp to zero for every for loop
        fgets(buffer, sizeof(buffer), pFile); //reading next line of /proc/stat        
        sscanf(buffer, "%*s %d", &cpu_user[i]); //saving 2nd line of /proc/stat ---> to extern int array
        char *token = strtok(buffer, " "); //setting token for new buffer
        while(token != NULL){   //token in NULL when there is nothing more in string to process
            if (sscanf(token, "%d", &temp) == 1){ //finding next decimal (sscanf returns 1 when it finds a match)
                cpu_sum[i] += temp; //sum of cpu usage for every core ---> to extern int array
            }
        token = strtok(NULL, " "); //going to next part of string when token found
        }
    }

    fclose(pFile);
    sem_post(&sem_a);
};