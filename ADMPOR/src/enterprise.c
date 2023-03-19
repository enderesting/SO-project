#include <stdio.h>
#include "memory.h"
#include "main.h"


/* 
* main comp. function. should execute infinite loop where:
    each iteration reads a op && data->terminate still == 0 
    processes it.

    if (id == -1) -> ignore, invalid 
    if (id == 1) -> order was given to terminate the program, return the number of processed operations
* can use other func in enterprise.h
*/
int execute_enterprise(int enterp_id, struct comm_buffers* buffers, struct main_data* data){}


/*
* reads the operation in buffer mem shared with intermd. and company with <enterp_id>
* before reading, check if (data->terminate == 1) -> immediately return function
* 
*/
void enterprise_receive_operation(struct operation* op, int enterp_id, struct comm_buffers* buffers, struct main_data* data){}


/* 
* func that process an operation, change its <receiving_enterp> field to <enterp_id>
* change the state to 'E' or 'A' depending on num of max op. reached.
* op. counter++. updates the operation in data structure
*/
void enterprise_process_operation(struct operation* op, int enterp_id, struct main_data* data, int* counter){}