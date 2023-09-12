#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

#include "functions.h"

pthread_t thread_r;
pthread_t thread_a;
pthread_t thread_p;

sem_t sem_r;
sem_t sem_a;
sem_t sem_p;

void closing();

int main(){
    signal(SIGINT, closing);

    while(1){
    sem_init(&sem_r,0,1);
    sem_init(&sem_a,0,0);
    sem_init(&sem_p,0,0);

    pthread_create(&thread_r, NULL, reader, NULL);
    pthread_create(&thread_a, NULL, analyzer, NULL);
    pthread_create(&thread_p, NULL, printer, NULL);

    pthread_join(thread_r, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_p, NULL);

    sem_destroy(&sem_r);
    sem_destroy(&sem_a);
    sem_destroy(&sem_p);

    sleep(2);
    }

    return 0;
};

void closing(){
    printf("\nCleaning and closing...\n");

    pthread_join(thread_r, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_p, NULL);

    sem_destroy(&sem_r);
    sem_destroy(&sem_a);
    sem_destroy(&sem_p);

    printf("\nDONE!\n");
    exit(0);
};