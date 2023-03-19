#include <stdio.h>
#include "memory.h"
#include "main.h"

/*
* reads app args (max operations, shared buffer size, num of client + companies). keep in main_data
*/
void main_args(int argc, char* argv[], struct main_data* data) {

    data->max_ops = (int)argv[0];
    data->buffers_size = (int)argv[1];
    data->n_clients = (int)argv[2];
    data->n_intermediaries = (int)argv[3];
    data->n_enterprises = (int)argv[4];
}

/*
* reserves dynamic memory for AdmPor, arrays *_pids + *_stats of main_data
* can use create_dynamic_memory func
*/
void create_dynamic_memory_buffers(struct main_data* data) {

    data->client_pids = create_dynamic_memory;
    data->intermediary_pids = create_dynamic_memory;
    data->enterprise_pids = create_dynamic_memory;

    data->client_stats = create_dynamic_memory;
    data->intermediary_stats = create_dynamic_memory;
    data->enterprise_pids = create_dynamic_memory;
}

/*
* reserves the shared memory for AdmPor. reserve shared memory for all comm_buffers buffers,
* including buffers themselves, their pointers, array data->results,  variable data->terminate
* create_shared_memory can be used. 
* data->results must be bounded by the MAX_RESULTS constant
*/
void create_shared_memory_buffers(struct main_data* data, struct comm_buffers* buffers){}

/*
* func that iniciates client/interm/company processes. you can use launch_*
* store the pids in its respective arrays in data structure
* 
*/
void launch_processes(struct comm_buffers* buffers, struct main_data* data){}

/*
* user interact func to receive 4 commands
*/
void user_interaction(struct comm_buffers* buffers, struct main_data* data){}

/*
* creates a opertaion, defined by op_counter and data introduced
* in the memory buffer shared between main and clients. print operation ip and op_counter++
* never create more opertation than the size of array data->results.
*/
void create_request(int* op_counter, struct comm_buffers* buffers, struct main_data* data){}

/*
* func that reads operation id, user and see if its valid
* yes -> print same info: state, cliente id, company requested, 
* client interm company id that received and processed
* no -> ??????
*/
void read_status(struct main_data* data){}

/*
* func that stops AdmPor.
* set flag data->terminate to 1
* wait for child processes to finish. 
* write stats at end of program. free reserved shared/dynamic memory
* use other main.h aux funcs
*/
void stop_execution(struct main_data* data, struct comm_buffers* buffers){}

/* 
* waits all processes to end, using wait_process do process.h
*/
void wait_processes(struct main_data* data){}

/*
* func that prints AdmPor final stats aka how many process processed by everyone.
*/
void write_statistics(struct main_data* data){}

/*
* func that frees all buffers of dynamic/shared memory in data struct
*/
void destroy_memory_buffers(struct main_data* data, struct comm_buffers* buffers){}
