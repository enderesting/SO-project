#include <stdlib.h>
#include <stdio.h>
#include "aptime.h"
#include "main.h"
#include <time.h>


struct tm get_time() {

    struct tm* time_1;
    time_t actual_time;

    actual_time = time((time_t*)NULL);
    time_1 = localtime(&actual_time);

    return *time_1;
}