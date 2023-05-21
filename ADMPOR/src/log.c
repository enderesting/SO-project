#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "main.h"
#include <string.h>
#include <time.h>

void log_op(struct main_data *data, int client, int enterp) {

    char* string;
    char s[100] = {};
    string = s;

    struct tm* time_1;
    time_t actual_time;

    actual_time = time((time_t*)NULL);
    time_1 = localtime(&actual_time);
    char* help = tmToString(*time_1);
    strcat(string, help);
    strcat(string, " op ");
    char* string_c;
    char s_c[50] = {};
    string_c = s_c;
    sprintf(string_c, "%d ", client);
    strcat(string, string_c);
    char* string_e;
    char s_e[50] = {};
    string_e = s_e;
    sprintf(string_e, "%d\n", enterp);
    strcat(string, string_e);


    fprintf(data->log_filename, "%s", string);
}

void log_status(struct main_data *data, int num) {

    char* string;
    char s[100] = {};
    string = s;

    struct tm* time_1;
    time_t actual_time;

    actual_time = time((time_t*)NULL);
    time_1 = localtime(&actual_time);
    char* help = tmToString(*time_1);
    strcat(string, help);
    strcat(string, " status ");
    char* string_num;
    char s_num[50] = {};
    string_num = s_num;
    sprintf(string_num, "%d\n", num);
    strcat(string, string_num);

    fprintf(data->log_filename, "%s", string);
}

void log_help(struct main_data *data) {

    char* string;
    char s[100] = {};
    string = s;

    struct tm* time_1;
    time_t actual_time;

    actual_time = time((time_t*)NULL);
    time_1 = localtime(&actual_time);
    char* help = tmToString(*time_1);
    strcat(string, help);
    strcat(string, " help\n");

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
    strcat(string, " stop\n");

    fprintf(data->log_filename, "%s", string);
}

char *tmToString(struct tm time) {

    char* result;
    char s[350] = {};
    result = s;

    char* year_str;
    char year_temp[50] = {};
    year_str = year_temp;

    int year = time.tm_year + 1900;

    char* mth_str;
    char mth_temp[50] = {};
    mth_str = mth_temp;

    int month = time.tm_mon + 1;

    char* day_str;
    char day_temp[50] = {};
    day_str = day_temp;

    int day = time.tm_mday;

    char* hour_str;
    char hour_temp[50] = {};
    hour_str = hour_temp;

    int hour = time.tm_hour;

    char* min_str;
    char min_temp[50] = {};
    min_str = min_temp;

    int min = time.tm_min;

    char* sec_str;
    char sec_temp[50] = {};
    sec_str = sec_temp;

    int sec = time.tm_sec;

    sprintf(year_str, "%d-", year);
    strcat(result, year_str);
    sprintf(mth_str, "%d-", month);
    strcat(result, mth_str);
    sprintf(day_str, "%d ", day);
    strcat(result, day_str);
    sprintf(hour_str, "%d:", hour);
    strcat(result, hour_str);
    sprintf(min_str, "%d:", min);
    strcat(result, min_str);
    sprintf(sec_str, "%d", sec);
    strcat(result, sec_str);

    return result;
}