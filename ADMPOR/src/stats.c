#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "main.h"
#include <string.h>
#include <time.h>
#include "log.h"

void write_stats(struct main_data* data, struct operation* op) {

    fprintf(data->statistics_filename, "Process statistics:\n");
    write_statistics(data);
    fprintf(data->statistics_filename, "\nRequest statistics:\n");

    for(int i = 0; i < 1; i++) {

        fprintf(data->statistics_filename, "Request: %d\n", op[i].id);
        fprintf(data->statistics_filename, "Status: %c\n", op[i].status);
        fprintf(data->statistics_filename, "Client id: %d\n", op[i].receiving_client);
        fprintf(data->statistics_filename, "Intermediary id: %d\n", op[i].receiving_interm);
        fprintf(data->statistics_filename, "Enterprise id: %d\n", op[i].receiving_enterp);
        fprintf(data->statistics_filename, "Start time: %s\n", tmToString(op[i].start_time));
        fprintf(data->statistics_filename, "Client time: %s\n", tmToString(op[i].start_time));
        fprintf(data->statistics_filename, "Intermediary time: %s\n", tmToString(op[i].start_time));
        fprintf(data->statistics_filename, "Enterprise time: %s\n", tmToString(op[i].start_time));
    }
}