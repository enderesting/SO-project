#include <stdlib.h>
#include <stdio.h>
#include "aptime.h"
#include "main.h"
#include <time.h>


struct timespec get_time() {

    struct timespec actual_time;
    
    if(clock_gettime(CLOCK_REALTIME, &actual_time) == 1) {

        printf("ERRO");
        exit(1);
    }

    return actual_time;
}