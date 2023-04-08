#include <stdio.h>
#include "memory.h"
#include "main.h"

int main(int argc, char *argv[]){
    struct main_data* mainData;
    struct comm_buffers* commBuffers;
    main_args(argc, argv, mainData);
    create_dynamic_memory_buffers(mainData);
    create_shared_memory_buffers(mainData,commBuffers);
}

/*
* reads app args (max operations, shared buffer size,
* num of client + intermediates + companies). keep in main_data
*/
void main_args(int argc, char* argv[], struct main_data* data) {
    if (argc == 5){
        data->max_ops = (int)argv[0];
        data->buffers_size = (int)argv[1];
        data->n_clients = (int)argv[2];
        data->n_intermediaries = (int)argv[3];
        data->n_enterprises = (int)argv[4];
    }
}

/*
* reserves dynamic memory for AdmPor, arrays *_pids + *_stats of main_data
* can use create_dynamic_memory func
*/
void create_dynamic_memory_buffers(struct main_data* data) {
    int intSize = sizeof(int);
    data->client_pids = create_dynamic_memory(intSize);
    data->intermediary_pids = create_dynamic_memory(intSize);
    data->enterprise_pids = create_dynamic_memory(intSize); 
    // process ids are different, this just initiates the pointer -- they need to be filled
    data->client_stats = create_dynamic_memory((data->n_clients)*intSize);
    data->intermediary_stats = create_dynamic_memory((data->n_intermediaries)*intSize);
    data->enterprise_stats = create_dynamic_memory((data->n_enterprises)*intSize);
}

/*
* reserves the shared memory for AdmPor. reserve shared memory for all comm_buffers buffers,
* including buffers themselves, their pointers, array data->results,  variable data->terminate
* create_shared_memory can be used. 
* data->results must be bounded by the MAX_RESULTS constant
*/
void create_shared_memory_buffers(struct main_data* data, struct comm_buffers* buffers){
    //buffer pointers
    int buffSize = data->buffers_size;
    buffers->main_client = create_shared_memory('main_client', buffSize);
    buffers->client_interm = create_shared_memory('client_interm', buffSize);
    buffers->interm_enterp = create_shared_memory('interm_enterp', buffSize);

    //ptrs -> pointing at every element
    buffers->main_client->ptrs = buffers->main_client;
    buffers->client_interm->ptrs = buffers->client_interm;
    buffers->interm_enterp->ptrs = buffers->interm_enterp;

    // point their actual ptrs at the beginning too?
    data->results = create_shared_memory('results', (data->max_ops)*sizeof(struct operation));
    data->terminate = create_shared_memory('terminate',sizeof(int));
}

/*
* func that iniciates client/interm/company processes. you can use launch_*
* store the pids in its respective arrays in data structure
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
