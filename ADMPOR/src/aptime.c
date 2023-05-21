/*
 * Grupo: SO-001
 * José "Emily" Sá   fc58200
 * Yichen Cao "Mimi" fc58165
 * Gonçalo Fernandes fc58194
 */

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