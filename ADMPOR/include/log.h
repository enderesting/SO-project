#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void log_op (struct main_data* data, int client, int enterp);

void log_status (struct main_data* data, int op);

void log_help (struct main_data* data);

void log_stop (struct main_data* data);

char* tmToString (struct tm time);
