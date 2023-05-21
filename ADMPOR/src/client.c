/*
 * Grupo: SO-001
 * José "Emily" Sá   fc58200
 * Yichen Cao "Mimi" fc58165
 * Gonçalo Fernandes fc58194
 */
#include <stdio.h>
#include "memory.h"
#include "memory-private.h"
#include "main.h"
#include "client.h"
#include "synchronization.h"
#include <unistd.h>
#include <stdlib.h>


/* 
* main comp. function. should execute infinite loop where:
    each iteration reads a main op && data->terminate still == 0 
    processes it.

    if (id == -1) -> ignore, invalid 
    if (id == 1) -> order was given to terminate the program, return the number of processed operations
* can use other func in client.h.
*/
int execute_client(int client_id, struct comm_buffers* buffers, struct main_data* data,  struct semaphores* sems){
    int isEnding = *(data->terminate);
    while (isEnding != 1) {
        // sleep(10);
        if(isEnding == -1) {
            printf("Error");
        }
        else if(isEnding == 0) {
            // printf("we're in execute_client!\n");
            // int *ptr = buffers->main_client->ptrs;
            struct operation *op = calloc(1,sizeof(struct operation));
            client_get_operation(op, client_id, buffers, data, sems);
            // printf("clien\n");
            if(op->id !=-1){
                // printf("found, process in client\n");
                client_process_operation(op, client_id, data, data->client_stats,sems);
                client_send_operation(op, buffers, data, sems);
            }
            free(op);
        }
        isEnding = *(data->terminate);
    }
    return data->client_stats[client_id]; //remember the data?
}


/*
* reads the operation in buffer mem shared with main & client with <client_id>
* before reading, check if (data->terminate == 1) -> immediately return function
*/
void client_get_operation(struct operation* op, int client_id, struct comm_buffers* buffers, struct main_data* data, struct semaphores* sems){

    if (*(data->terminate) != 1){
        consume_begin(sems->main_client);
        // printf("Reading: Main-Client\n");
        //?????? it doesnt go any further???
        read_main_client_buffer(buffers->main_client, client_id, data->buffers_size, op);
        consume_end(sems->main_client);
        // printf("Reading: Main-Client DONE!\n");
    }
}


/*
* func that process an operation, change its <receiving_client> field to <client_id>
* change the state to 'C'.
* op. counter++. updates the operation in data structure
*/
void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter, struct semaphores* sems){
    //printf("HEY I'M HERE\n");
    op->receiving_client = client_id;
    op->status = 'C';
    // printf("Processing: Client begin");
    semaphore_mutex_lock(sems->results_mutex); //stuck here?
    printf("Processing: Client in process\n");
    data->results[op->id] = *op; // <-- i wonder if we should change each stat individually instead
    semaphore_mutex_unlock(sems->results_mutex);
    // printf("Processing: Client DONE!");
    counter[client_id]++;
}

/*
* func that writes an operation in buffer mem shared between clients and intermed.
*/
void client_send_operation(struct operation* op, struct comm_buffers* buffers, struct main_data* data, struct semaphores* sems){
    produce_begin(sems->client_interm);
    // printf("Writing: Client-Interm\n");
    write_client_interm_buffer(buffers->client_interm, data->buffers_size, op);
    produce_end(sems->client_interm);
    // printf("Writing: Client-Interm DONE!\n");
}