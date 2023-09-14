#include <stdio.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>

#include "functions.h"

//global semaphores definition
sem_t sem_r;
sem_t sem_a;
sem_t sem_p;

//global threads names definition
pthread_t thread_r;
pthread_t thread_a;
pthread_t thread_p;
pthread_t thread_w;
pthread_t thread_l;

//global flags definition
bool terminate_flag;
bool alive_r;
bool alive_a;
bool alive_p;

//global message definition
const char *message;

//local finctions prototypes
void t_reader();
void t_analyzerAndPrinter();
void t_watchdog();
void t_logger();

int main(){
    //global semaphores initalization
    sem_init(&sem_r,0,1);
    sem_init(&sem_a,0,0);
    sem_init(&sem_p,0,0);

    //initalazing tests
    t_reader();
    t_analyzerAndPrinter();
    t_watchdog();
    t_logger();

    //destroying semaphores
    sem_destroy(&sem_r);
    sem_destroy(&sem_a);
    sem_destroy(&sem_p);

    return 0;
}

//reader() test
void t_reader(){
    //initalizing reader()
    pthread_create(&thread_r, NULL, reader, NULL);
    pthread_join(thread_r, NULL);

    //making sure that data was writen in arrays
    for(int i=0; i<16; i++){
        assert(cpu_user[i]);
        assert(cpu_sum[i]);
    }
    printf("\nreader.c - PASS");
}

//analyzer and printer test
void t_analyzerAndPrinter(){
    //initalizing analyzer()
    pthread_create(&thread_a, NULL, analyzer, NULL);
    pthread_join(thread_a, NULL);
    
    //making sure that calculations result were written into an array
    for(int i=0; i<16; i++){
        assert(cpu_proc[i]);
    }
    printf("\nanalyzer and printer.c - PASS");
}  

//watchdog test
void t_watchdog(){
    //checking if watchdog will find a dead reader()
    alive_r = false;
    alive_a = true;
    alive_r = true;
    terminate_flag = false;

    pthread_create(&thread_w, NULL, watchdog, NULL); 
    sleep(2);

    assert(terminate_flag == true);
    pthread_join(thread_w, NULL);

    //checking if watchdog will find a dead analyzer()
    alive_r = true;
    alive_a = false;
    terminate_flag = false;

    pthread_create(&thread_w, NULL, watchdog, NULL); 
    sleep(2);

    assert(terminate_flag == true);
    pthread_join(thread_w, NULL);

    //checking if watchdog will find a dead printer()
    alive_a = true;
    alive_r = false;
    terminate_flag = false;

    pthread_create(&thread_w, NULL, watchdog, NULL); 
    sleep(2);

    assert(terminate_flag == true);
    pthread_join(thread_w, NULL);

    //checking if watchdog will close after terminate flag was set up
    alive_r = true;
    alive_a = true;
    alive_r = true;
    terminate_flag = true;

    pthread_create(&thread_w, NULL, watchdog, NULL); 
    sleep(2);

    assert(terminate_flag == true);
    pthread_join(thread_w, NULL);

    printf("\nwatchdog.c - PASS");
}

//logger test
void t_logger(){
    //geting info about log.txt size bofore logger use
    struct stat log_before;
    struct stat log_after;
    stat("log.txt", &log_before);

    //writing message to log.txt
    message = "Logger test --- PASS!";

    pthread_create(&thread_l, NULL, logger, NULL);
    pthread_join(thread_l, NULL);

    //geting info about log.txt size after logger use
    stat("log.txt", &log_after);
    //checking if size after is greater then size before, if so logger works corectly
    if (log_after.st_size > log_before.st_size){
        printf("\nlogger.c - PASS");
    } else {
        printf("\nlogger.c - FAIL");
    }
}