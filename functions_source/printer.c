#include <stdio.h>

#include "../funkctions.h"

void printer(){
    for(int i = 0; i < 16 ; i++){
        printf("\nCPU%d: %7.2lf%%", i, cpu_proc[i]);
    }
}