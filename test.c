#include <stdio.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#include "functions.h"

sem_t sem_r;
sem_t sem_a;
sem_t sem_p;

pthread_t thread_r;
pthread_t thread_a;
pthread_t thread_p;
pthread_t thread_w;

bool watchdog_flag;
bool alive_r;
bool alive_a;
bool alive_p;

void t_reader();
void t_analyzerAndPrinter();
void t_watchdog();

int main(){
    sem_init(&sem_r,0,1);
    sem_init(&sem_a,0,0);
    sem_init(&sem_p,0,0);

    t_reader();
    t_analyzerAndPrinter();
    t_watchdog();

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

void t_watchdog(){
    alive_r = false;
    alive_a = true;
    alive_r = true;
    watchdog_flag = false;

    pthread_create(&thread_w, NULL, watchdog, NULL); 
    sleep(2);

    assert(watchdog_flag == true);
    pthread_join(thread_w, NULL);

    alive_r = true;
    alive_a = false;
    watchdog_flag = false;

    pthread_create(&thread_w, NULL, watchdog, NULL); 
    sleep(2);

    assert(watchdog_flag == true);
    pthread_join(thread_w, NULL);

    alive_a = true;
    alive_r = false;
    watchdog_flag = false;

    pthread_create(&thread_w, NULL, watchdog, NULL); 
    sleep(2);

    assert(watchdog_flag == true);
    pthread_join(thread_w, NULL);

    alive_r = true;
    alive_a = true;
    alive_r = true;
    watchdog_flag = true;

    pthread_create(&thread_w, NULL, watchdog, NULL); 
    sleep(2);

    assert(watchdog_flag == true);
    pthread_join(thread_w, NULL);

    printf("\n watchdog.c - PASS");
}