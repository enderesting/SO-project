/*
 * Grupo: SO-001
 * José "Emily" Sá   fc58200
 * Yichen Cao "Mimi" fc58165
 * Gonçalo Fernandes fc58194
 */

#include <unistd.h>
#include "apsignal.h"
#include "main.h"


void handler()
{
    pid_t pid = getpid(); 
    if(pid == *data->parent_pid){//only execute stop_execution for main process
        stop_execution(data, buffers, sems);
    }
}

void write_alarm()
{
    while (1)
    {
        sleep(*data->alarm_time);
        for (int i = 0; i < data->max_ops; i++)
        {
            struct operation next = data->results[i];
            printf("op: %d status: %c start_time: %ld client: %d client_time: %ld intermediary: %d intermediary_time: %ld enterprise: %d enterprise_time: %ld",
                   next.id, next.status, next.start_time.tv_sec, next.receiving_client, next.client_time.tv_sec,
                   next.receiving_interm, next.intermed_time.tv_sec, next.receiving_enterp, next.enterp_time.tv_sec);
        }
    }
}