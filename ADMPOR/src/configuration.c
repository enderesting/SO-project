#include <stdlib.h>
#include <stdio.h>
#include "configuration.h"
#include "main.h"

void read_arguments(char *file_name, struct main_data *data)
{
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Erro ao abrir ficheiro\n");
        exit(0);
    }

    fscanf(file, "%d", &(data->max_ops));
    fscanf(file, "%d", &(data->buffers_size));
    fscanf(file, "%d", &(data->n_clients));
    fscanf(file, "%d", &(data->n_intermediaries));
    fscanf(file, "%d", &(data->n_enterprises));
    fscanf(file, "%s", &(data->log_filename));
    fscanf(file, "%s", &(data->statistics_filename));
    fscanf(file, "%d", &(data->alarm_time));

    fclose(file);
}