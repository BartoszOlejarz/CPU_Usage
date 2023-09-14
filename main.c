#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

#include "functions.h"

const char *message;

pthread_t thread_r;
pthread_t thread_a;
pthread_t thread_p;
pthread_t thread_w;
pthread_t thread_l;

sem_t sem_r;
sem_t sem_a;
sem_t sem_p;

void closing();

bool terminate_flag;
bool alive_r;
bool alive_a;
bool alive_p;

int main(){
    signal(SIGINT, closing);
    
    if(sem_init(&sem_r,0,1) != 0){
        message = "main.c - reader() semapthore not opened!";
        terminate_flag = true;
    }
    if(sem_init(&sem_a,0,0) != 0){
        message = "main.c - reader() semapthore not opened!";
        terminate_flag = true;
    }
    if(sem_init(&sem_p,0,0) != 0){
        message = "main.c - reader() semapthore not opened!";
        terminate_flag = true;
    }

    terminate_flag = false;

    if(pthread_create(&thread_w, NULL, watchdog, NULL) != 0){
        message = "main.c - watchdog() thread not opened!";
        terminate_flag = true;
    }
    
    while(1){
    alive_r = false;
    alive_a = false;
    alive_p = false;

    if(pthread_create(&thread_r, NULL, reader, NULL) != 0){
        message = "main.c - reader() thread not opened!";
        terminate_flag = true;
    }
    if(pthread_create(&thread_a, NULL, analyzer, NULL) != 0){
        message = "main.c - analyzer() thread not opened!";
        terminate_flag = true;
    }
    if(pthread_create(&thread_p, NULL, printer, NULL) != 0){
        message = "main.c - printer() thread not opened!";
        terminate_flag = true;
    }

    pthread_join(thread_r, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_p, NULL);

    if(terminate_flag == true){
        pthread_create(&thread_l, NULL, logger, NULL);
        pthread_join(thread_l, NULL);
        closing();
    }

    sleep(2);
    }

    return 0;
};

void closing(){
    printf("\nCleaning and closing...\n");

    terminate_flag = true;
    
    pthread_join(thread_r, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_p, NULL);
    pthread_join(thread_w, NULL);

    sem_destroy(&sem_r);
    sem_destroy(&sem_a);
    sem_destroy(&sem_p);

    printf("\nDONE!\n");
    exit(0);
};