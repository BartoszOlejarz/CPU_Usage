#include <stdio.h>

#include "../funkctions.h"

float cpu_proc[16];

void analyzer(){
    for(int i = 0; i < 16; i++){
        cpu_proc[i] = ((float)cpu_user[i]/(float)cpu_sum[i])*100;
    }
}