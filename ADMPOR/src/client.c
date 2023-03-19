#include <stdio.h>
#include "memory.h"
#include "main.h"

/* 
* main comp. function. should execute infinite loop where:
    each iteration reads a main op && data->terminate still == 0 
    processes it.

    if (id == -1) -> ignore, invalid 
    if (id == 1) -> order was given to terminate the program, return the number of processed operations
* can use other func in client.h.
*/
int execute_client(int client_id, struct comm_buffers* buffers, struct main_data* data){}


/*
* reads the operation in buffer mem shared with main & client with <client_id>
* before reading, check if (data->terminate == 1) -> immediately return function
*/
void client_get_operation(struct operation* op, int client_id, struct comm_buffers* buffers, struct main_data* data){}


/*
* func that process an operation, change its <receiving_client> field to <client_id>
* change the state to 'C'.
* op. counter++. updates the operation in data structure
*/
void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter){}

/*
* func that writes an operation in buffer mem shared between clients and intermed.
*/
void client_send_operation(struct operation* op, struct comm_buffers* buffers, struct main_data* data){}