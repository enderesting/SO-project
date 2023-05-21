#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "main.h"
#include <string.h>
#include "log.h"

void write_stats(struct main_data* data, struct operation* op) {

    fprintf(data->statistics_filename, "Process statistics:\n");
    write_statistics(data);
    fprintf(data->statistics_filename, "\nRequest statistics:\n");

    int max = 0;

    for(int i = 0; i < data->n_clients; i++){

        max = max + data->client_stats[i];
    }

    for(int i = 0; i < max; i++) {

        fprintf(data->statistics_filename, "Request: %d\n", op[i].id);
        fprintf(data->statistics_filename, "Status: %c\n", op[i].status);
        fprintf(data->statistics_filename, "Client id: %d\n", op[i].receiving_client);
        fprintf(data->statistics_filename, "Intermediary id: %d\n", op[i].receiving_interm);
        fprintf(data->statistics_filename, "Enterprise id: %d\n", op[i].receiving_enterp);
        fprintf(data->statistics_filename, "Start time: %s\n", toStringStats(op[i].start_time));
        fprintf(data->statistics_filename, "Client time: %s\n", toStringStats(op[i].client_time));
        fprintf(data->statistics_filename, "Intermediary time: %s\n", toStringStats(op[i].intermed_time));
        fprintf(data->statistics_filename, "Enterprise time: %s\n", toStringStats(op[i].enterp_time));
        fprintf(data->statistics_filename, "Total time: %ld\n\n", (op[i].enterp_time.tv_nsec-op[i].start_time.tv_nsec)/1000000);
    }
}

char* toStringStats(struct timespec time){

    char* result;
    char s[350] = {};
    result = s;
    struct tm* new_time;
    new_time = localtime(&time.tv_sec);
    char* temp = tmToString(*new_time);
    char* temp2;
    char temp3[350] = {};
    temp2 = temp3;
    strcat(result, temp);
    strcat(result, ".");
    sprintf(temp2, "%ld", time.tv_nsec/1000000);
    strcat(result, temp2);

    return result;
}