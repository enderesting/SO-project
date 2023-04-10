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

/*
* main intm. function. should execute infinite loop where:
    each iteration reads a client op w/ id != -1 && data->terminate still == 0
    processes it and sends to company.

    if (id == -1) -> ignore, invalid
    if (id == 1) -> order was given to terminate the program, return the number of processed operations
* can use other func in intermediary.h
*/
int execute_intermediary(int interm_id, struct comm_buffers *buffers, struct main_data *data)
{
    int check = 1;
    while (check == 1)
    {
        struct operation *op =  buffers->main_client->buffer;
        int id = *(data->terminate);

        if (id == 0)
        {
            intermediary_receive_operation(op, buffers, data);
            intermediary_process_operation(op, interm_id, data, data->intermediary_stats);
            intermediary_send_answer(op, buffers, data);
        }
        else if (id == -1)
        {
            printf("Error");
        }
        else if(id == 1)
        {
            check = 0;
        }
    }
    return data->intermediary_stats[interm_id];
}

/*
 * reads the operation in buffer mem shared with clients and intermd.
 * before reading, check if (data->terminate == 1) -> immediately return function
 */
void intermediary_receive_operation(struct operation *op, struct comm_buffers *buffers, struct main_data *data)
{
    if (*(data->terminate) != 1)
    {
        struct circular_buffer *buffer = buffers->client_interm;
        read_client_interm_buffer(buffer, data->buffers_size, op);
    }
}

/* Função que processa uma operação, alterando o seu campo receiving_intermediary para o id
 * passado como argumento, alterando o estado da mesma para 'I' (intermediary), e
 * incrementando o contador de operações. Atualiza também a operação na estrutura data.
 *
 * func that process an operation, change its <receiving_intermediary> field for  <interm_id>
 * change the state to 'I', op. counter++. updates the operation in data structure
 */
void intermediary_process_operation(struct operation *op, int interm_id, struct main_data *data, int *counter)
{
    op->receiving_interm = interm_id;
    op->status = 'I';
    data->results->receiving_interm = interm_id;
    data->results->status = 'I';
    counter[interm_id]++;
}

/*
 * func that writes an op. in buffer mem between intermed. and company
 */
void intermediary_send_answer(struct operation *op, struct comm_buffers *buffers, struct main_data *data)
{
    write_interm_enterp_buffer(buffers->interm_enterp, data->buffers_size, op);
}
