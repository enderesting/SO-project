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
#include "enterprise.h"
#include "synchronization.h"
#include <unistd.h>
#include <stdlib.h>
#include "aptime.h"


/* 
* main comp. function. should execute infinite loop where:
    each iteration reads a op && data->terminate still == 0 
    processes it.

    if (id == -1) -> ignore, invalid 
    if (id == 1) -> order was given to terminate the program, return the number of processed operations
* can use other func in enterprise.h
*/
int execute_enterprise(int enterp_id, struct comm_buffers* buffers, struct main_data* data, struct semaphores* sems){
    int isEnding = *(data->terminate);
    while (isEnding != 1) {
        if(isEnding == -1) {
            printf("Error");
        }
        else if(isEnding == 0) {
            // printf("we're in execute_enterprise!\n");
            // int *ptr = buffers->interm_enterp->ptrs;
            // struct operation *buff_ptr = buffers->interm_enterp->buffer;
            struct operation *op = calloc(1,sizeof(struct operation));
            enterprise_receive_operation(op, enterp_id, buffers, data, sems);
            // printf("eneteer\n");
            if(op->id != -1){
                printf("found, process in enterprise\n");
                enterprise_process_operation(op, enterp_id, data, data->enterprise_stats, sems);
            }
            free(op);
        }
        isEnding = *(data->terminate);
        sleep(1);
    }
    return data->client_stats[enterp_id]; //remember the data?

}


/*
* reads the operation in buffer mem shared with intermd. and company with <enterp_id>
* before reading, check if (data->terminate == 1) -> immediately return function
* 
*/
void enterprise_receive_operation(struct operation* op, int enterp_id, struct comm_buffers* buffers, struct main_data* data, struct semaphores* sems){
    if (*(data->terminate) != 1){
        consume_begin(sems->interm_enterp);
        read_interm_enterp_buffer(buffers->interm_enterp, enterp_id, data->buffers_size, op);
        consume_end(sems->interm_enterp);
        op->enterp_time = get_time();
    }
}


/* 
* func that process an operation, change its <receiving_enterp> field to <enterp_id>
* change the state to 'E' or 'A' depending on num of max op. reached.
* op. counter++. updates the operation in data structure
*/
void enterprise_process_operation(struct operation* op, int enterp_id, struct main_data* data, int* counter, struct semaphores* sems){

    int op_id = op->id;
    if (op_id < (data->max_ops)) {
        op->status = 'E';
    }else {
        op->status = 'A';
    }
    op->receiving_enterp = enterp_id;
    semaphore_mutex_lock(sems->results_mutex);
    data->results[op->id] = *op;
    semaphore_mutex_unlock(sems->results_mutex);
    counter[enterp_id]++;
}