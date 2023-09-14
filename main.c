#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

#include "functions.h"

//global massage definition
const char *message;

//global thread names definition
pthread_t thread_r;
pthread_t thread_a;
pthread_t thread_p;
pthread_t thread_w;
pthread_t thread_l;

//global semaphore names definition
sem_t sem_r;
sem_t sem_a;
sem_t sem_p;

//global bool flags definition
bool terminate_flag;
bool alive_r;
bool alive_a;
bool alive_p;

//global closing function prototype
void closing();

int main(){
    signal(SIGINT, closing); //Ctrl+C signal handling
    
    //semaphore initialization with error handling
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

    //making sure terminate_flag is false at the begining
    terminate_flag = false;

    //creating watchdog thread wtih error handling
    if(pthread_create(&thread_w, NULL, watchdog, NULL) != 0){
        message = "main.c - watchdog() thread not opened!";
        terminate_flag = true;
    }
    
    //main app loop
    while(1){
    //making all alive flags false
    alive_r = false;
    alive_a = false;
    alive_p = false;

    //thread creation with error handling
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

    //waiting for threads to finish
    pthread_join(thread_r, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_p, NULL);

    //checking if terminate flag i up. If yes logger is initialized, error message is writen into log.txt and closing() is initialized
    if(terminate_flag == true){
        pthread_create(&thread_l, NULL, logger, NULL);
        pthread_join(thread_l, NULL);
        closing();
    }

    //waiting 2 second for next loop
    sleep(2);
    }

    return 0;
};

//closing () that makes sure everyting is safely closed
void closing(){
    printf("\nCleaning and closing...\n");

    //setting terminate flag up for watchdog() loop to close
    terminate_flag = true;
    
    //waiting for threads to finish
    pthread_join(thread_r, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_p, NULL);
    pthread_join(thread_w, NULL);

    //destroying semaphores
    sem_destroy(&sem_r);
    sem_destroy(&sem_a);
    sem_destroy(&sem_p);

    printf("\nDONE!\n");
    //exiting app
    exit(0);
};