#include <stdio.h>
#include "memory.h"
#include "main.h"

/* 
* main intm. function. should execute infinite loop where:
    each iteration reads a client op w/ id != -1 && data->terminate still == 0 
    processes it and sends to company.

    if (id == -1) -> ignore, invalid 
    if (id == 1) -> order was given to terminate the program, return the number of processed operations
* can use other func in intermediary.h
*/
int execute_intermediary(int interm_id, struct comm_buffers* buffers, struct main_data* data){}


/* 
* reads the operation in buffer mem shared with clients and intermd.
* before reading, check if (data->terminate == 1) -> immediately return function
*/
void intermediary_receive_operation(struct operation* op, struct comm_buffers* buffers, struct main_data* data){}


/* 
* func that process an operation, change its <receiving_intermediary> field for  <interm_id>
* change the state to 'I', op. counter++. updates the operation in data structure
*/
void intermediary_process_operation(struct operation* op, int interm_id, struct main_data* data, int* counter){}


/*
* func that writes an op. in buffer mem between intermed. and company
*/
void intermediary_send_answer(struct operation* op, struct comm_buffers* buffers, struct main_data* data){}