#include <pthread.h>
#include <semaphore.h>

extern pthread_t thread_r;
extern pthread_t thread_a;
extern pthread_t thread_p;

extern sem_t sem_r;
extern sem_t sem_a;
extern sem_t sem_p;


extern int cpu_user[16];
extern int cpu_sum[16];
extern float cpu_proc[16];

void *reader();
void *analyzer();
void *printer();
void *logger();
void *watchdog();