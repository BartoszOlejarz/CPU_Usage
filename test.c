#include <stdio.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>

#include "functions.h"

sem_t sem_r;
sem_t sem_a;
sem_t sem_p;

pthread_t thread_r;
pthread_t thread_a;
pthread_t thread_p;

void t_reader();
void t_analyzerAndPrinter();

int main(){
    sem_init(&sem_r,0,1);
    sem_init(&sem_a,0,0);
    sem_init(&sem_p,0,0);

    t_reader();
    t_analyzerAndPrinter();

    sem_destroy(&sem_r);
    sem_destroy(&sem_a);
    sem_destroy(&sem_p);

    return 0;
}

void t_reader(){
    pthread_create(&thread_r, NULL, reader, NULL);

    pthread_join(thread_r, NULL);

    for(int i=0; i<16; i++){
        assert(cpu_user[i]);
        assert(cpu_sum[i]);
    }
    printf("\n reader.c - PASS");
}

void t_analyzerAndPrinter(){
    pthread_create(&thread_a, NULL, analyzer, NULL);

    pthread_join(thread_a, NULL);
    
    for(int i=0; i<16; i++){
        assert(cpu_proc[i]);
    }
    printf("\n analyzer and printer.c - PASS");
}  