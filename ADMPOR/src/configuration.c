#include <stdlib.h>
#include <stdio.h>
#include "configuration.h"
#include "main.h"

void read_arguments(char *file_name, struct main_data *data)
{
    FILE *file = fopen(file_name, "r");
    char contents[100];

    if (file == NULL)
    {
        printf("Erro ao abrir ficheiro\n");
        exit(0);
    }

    data->max_ops = atoi(fgets(contents, 100, file));
    data->buffers_size = atoi(fgets(contents, 100, file));
    data->n_clients = atoi(fgets(contents, 100, file));
    data->n_intermediaries = atoi(fgets(contents, 100, file));
    data->n_enterprises = atoi(fgets(contents, 100, file));
    data->log_filename = fopen(fgets(contents, 100, file), "w+");
    data->statistics_filename = fopen(fgets(contents, 100, file), "w+");
    data->alarm_time = atoi(fgets(contents, 100, file));

    fclose(file);

    data->terminate = 0;
}