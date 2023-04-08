#include <stdio.h>
#include "memory.h"
#include "main.h"

int main(int argc, char *argv[]) {
    //init data structures
    struct main_data* data = create_dynamic_memory(sizeof(struct main_data));
    struct comm_buffers* buffers = create_dynamic_memory(sizeof(struct comm_buffers));
    buffers->main_client = create_dynamic_memory(sizeof(struct rnd_access_buffer));
    buffers->client_interm = create_dynamic_memory(sizeof(struct circular_buffer));
    buffers->interm_enterp = create_dynamic_memory(sizeof(struct rnd_access_buffer));
    //execute main code
    main_args(argc, argv, data);
    create_dynamic_memory_buffers(data);
    create_shared_memory_buffers(data, buffers);
    launch_processes(buffers, data);
    user_interaction(buffers, data);
    //release memory before terminating
    destroy_dynamic_memory(data);
    destroy_dynamic_memory(buffers->main_client);
    destroy_dynamic_memory(buffers->client_interm);
    destroy_dynamic_memory(buffers->interm_enterp);
    destroy_dynamic_memory(buffers);
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
    data->client_pids = create_dynamic_memory((data->n_clients)*intSize);
    data->intermediary_pids = create_dynamic_memory((data->n_intermediaries)*intSize);
    data->enterprise_pids = create_dynamic_memory((data->n_enterprises)*intSize); 
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
void launch_processes(struct comm_buffers* buffers, struct main_data* data){
    for(int i = 0; i<(data->n_clients); i++){
        //!! currently assuming:
        // id: i, iterating thru 0 - n_clients
        // pid: returned after launch
        int pid = launch_client(i,buffers,data);
        data->client_pids[i] = pid;
    }

    for(int i = 0; i<(data->n_intermediaries); i++){
        int pid = launch_interm(i,buffers,data);
        data->intermediary_pids[i] = pid;
    }

    for(int i = 0; i<(data->n_enterprises); i++){
        int pid = launch_enterp(i,buffers,data);
        data->enterprise_pids[i] = pid;
    }
}

/*
* user interact func to receive 4 commands
*/
void user_interaction(struct comm_buffers* buffers, struct main_data* data){
    // reads user input
    // calls blah
}

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
