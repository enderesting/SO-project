/*
 * Grupo: SO-001
 * José "Emily" Sá   fc58200
 * Yichen Cao "Mimi" fc58165
 * Gonçalo Fernandes fc58194
 */
#include <stdio.h>
#include "memory.h"
#include "main.h"
#include "intermediary.h"
#include "synchronization.h"
#include <unistd.h>
#include <stdlib.h>
#include "aptime.h"


/*
* main intm. function. should execute infinite loop where:
    each iteration reads a client op w/ id != -1 && data->terminate still == 0
    processes it and sends to company.

    if (id == -1) -> ignore, invalid
    if (id == 1) -> order was given to terminate the program, return the number of processed operations
* can use other func in intermediary.h
*/
int execute_intermediary(int interm_id, struct comm_buffers *buffers, struct main_data *data, struct semaphores* sems)
{
    int isEnding = *(data->terminate);
    while (isEnding != 1) {
        // sleep(10);
        if(isEnding == -1) {
            printf("Error");
        }
        else if(isEnding == 0) {
            // printf("we're in execute_interm!\n");
                    struct operation *op = calloc(1,sizeof(struct operation));
                    intermediary_receive_operation(op, buffers, data, sems);
                    // printf("interm\n");
                    if (op->id != -1){
                        // printf("found, process in interm \n"); // its in here somehow
                        intermediary_process_operation(op, interm_id, data, data->intermediary_stats, sems);
                        intermediary_send_answer(op, buffers, data, sems);    
                    }
                    free(op);
        }
        isEnding = *(data->terminate);
    }
    return data->intermediary_stats[interm_id];
}

/*
 * reads the operation in buffer mem shared with clients and intermd.
 * before reading, check if (data->terminate == 1) -> immediately return function
 */
void intermediary_receive_operation(struct operation *op, struct comm_buffers *buffers, struct main_data *data, struct semaphores* sems)
{
    if (*(data->terminate) != 1){
        consume_begin(sems->client_interm);
        // printf("Reading: Client-Interm\n");
        read_client_interm_buffer(buffers->client_interm, data->buffers_size, op);
        consume_end(sems->client_interm);
        // printf("Reading: Client-Interm DONE!\n");
    }
}

/* Função que processa uma operação, alterando o seu campo receiving_intermediary para o id
 * passado como argumento, alterando o estado da mesma para 'I' (intermediary), e
 * incrementando o contador de operações. Atualiza também a operação na estrutura data.
 *
 * func that process an operation, change its <receiving_intermediary> field for  <interm_id>
 * change the state to 'I', op. counter++. updates the operation in data structure
 */
void intermediary_process_operation(struct operation *op, int interm_id, struct main_data *data, int *counter, struct semaphores* sems){
    op->receiving_interm = interm_id;
    op->status = 'I';
    op->intermed_time = get_time(); 
    counter[interm_id]++;
    // printf("Processing: Interm begin");
    semaphore_mutex_lock(sems->results_mutex);
    printf("Processing: Interm in process\n");
    data->results[op->id] = *op;
    semaphore_mutex_unlock(sems->results_mutex);
    // printf("Processing: Interm DONE!");
}

/*
 * func that writes an op. in buffer mem between intermed. and company
 */
void intermediary_send_answer(struct operation *op, struct comm_buffers *buffers, struct main_data *data, struct semaphores* sems)
{
    produce_begin(sems->interm_enterp);
    // printf("Writing: Interm-Enterp\n");
    write_interm_enterp_buffer(buffers->interm_enterp, data->buffers_size, op);
    produce_end(sems->interm_enterp);
    // printf("Writing: Interm-Enterp DONE!\n");
}
