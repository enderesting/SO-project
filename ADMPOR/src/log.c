#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "main.h"
#include <string.h>
#include <time.h>

void log_op(struct main_data *data, int client, int enterp) {
}

void log_status(struct main_data *data, int op) {
}

void log_help(struct main_data *data) {

    char* string;
    char s[100] = {};
    string = s;

    struct tm* time_1;
    time_t actual_time;

    actual_time = time((time_t*)NULL);
    time_1 = localtime(&actual_time);
    char* help = asctime(time_1);
    strcat(string, help);
    strcat(string, "help\n");

    fprintf(data->log_filename, "%s", string);
}

void log_stop(struct main_data *data) {

    char* string;
    char s[100] = {};
    string = s;

    struct tm* time_1;
    time_t actual_time;

    actual_time = time((time_t*)NULL);
    time_1 = localtime(&actual_time);
    char* stop =  tmToString(*time_1);
    strcat(string, stop);
    strcat(string, "stop\n");

    fprintf(data->log_filename, "%s", string);
}

char *tmToString(struct tm time) {


    return;
}
