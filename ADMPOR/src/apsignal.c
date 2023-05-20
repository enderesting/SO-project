#include "apsignal.h"
#include "main.h"

extern struct main_data *data;
extern struct comm_buffers *buffers;
extern struct semaphores *sems;

void handler(int signum)
{
    if (signum == SIGINT){
        printf("hiahaihaihi");
        stop_execution(data, buffers, sems);
    }
}

void write_alarm()
{
    while (1)
    {
        sleep(data->alarm_time);
        for (int i = 0; i < data->max_ops; i++)
        {
            struct operation next = data->results[i];
            printf("op: %d status: %c start_time: %d client: %d client_time: %d intermediary: %d intermediary_time: %d enterprise: %d enterprise_time: %d",
                   next.id, next.status, next.start_time, next.receiving_client, next.client_time,
                   next.receiving_interm, next.intermed_time, next.receiving_enterp, next.enterp_time);
        }
    }
}