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
#include <unistd.h>


/* 
* main comp. function. should execute infinite loop where:
    each iteration reads a main op && data->terminate still == 0 
    processes it.

    if (id == -1) -> ignore, invalid 
    if (id == 1) -> order was given to terminate the program, return the number of processed operations
* can use other func in client.h.
*/
int execute_client(int client_id, struct comm_buffers* buffers, struct main_data* data){
    int isEnding = *(data->terminate);
    while (isEnding != 1) {
        if(isEnding == -1) {
            printf("Error");
        }
        else if(isEnding == 0) {
            int *ptr = buffers->main_client->ptrs;
            struct operation *buff_ptr = buffers->main_client->buffer;

            for(int i = 0; i<(data->buffers_size); i++){
                if(ptr[i]==1 && (buff_ptr[i].requesting_client) == client_id){
                    struct operation *op = calloc(1,sizeof(struct operation));
                    client_get_operation(op, client_id, buffers, data);
                    client_process_operation(op, client_id, data, data->client_stats);
                    client_send_operation(op, buffers, data);
                    break;
                }
            }
        }
        isEnding = *(data->terminate);
        sleep(1);
    }
    return data->client_stats[client_id]; //remember the data?
}


/*
* reads the operation in buffer mem shared with main & client with <client_id>
* before reading, check if (data->terminate == 1) -> immediately return function
*/
void client_get_operation(struct operation* op, int client_id, struct comm_buffers* buffers, struct main_data* data){

    if (*(data->terminate) != 1){

        read_main_client_buffer(buffers->main_client, client_id, data->buffers_size, op);
        // client_process_operation(op, client_id, data, data->client_stats);
        // client_send_operation(op, buffers, data);
    }
}


/*
* func that process an operation, change its <receiving_client> field to <client_id>
* change the state to 'C'.
* op. counter++. updates the operation in data structure
*/
void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter){
    op->receiving_client = client_id;
    op->status = 'C';
    int op_id = op->id;
    data->results[op_id] = *op; // <-- i wonder if we should change each stat individually instead
    counter[client_id]++;
}

/*
* func that writes an operation in buffer mem shared between clients and intermed.
*/
void client_send_operation(struct operation* op, struct comm_buffers* buffers, struct main_data* data){
    write_client_interm_buffer(buffers->client_interm, data->buffers_size, op);
}