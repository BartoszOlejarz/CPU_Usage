#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

//global message for logger
extern const char *message;

//threads names
extern pthread_t thread_r;
extern pthread_t thread_a;
extern pthread_t thread_p;
extern pthread_t thread_w;
extern pthread_t thread_l;

//semaphore names
extern sem_t sem_r;
extern sem_t sem_a;
extern sem_t sem_p;

//checking flags
extern bool alive_r;
extern bool alive_a;
extern bool alive_p;
extern bool terminate_flag;

//arrays for main calcluations
extern int cpu_user[16];
extern int cpu_sum[16];
extern float cpu_proc[16];

//functions prototypes
void *reader();
void *analyzer();
void *printer();
void *watchdog();
void *logger();