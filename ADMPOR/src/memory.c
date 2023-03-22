#include <stdio.h>
#include <stdlib.h>

/*
* reserves a shared memory zone with <size> & <name>. fill the zone with 0
* return pointer. concatenate the result using func getuid()
* to make the name unique to the process.
*/
void* create_shared_memory(char* name, int size){}


/* 
* func that reserves a dynamic space of size. fill the zone with 0
* return pointer
*/
void* create_dynamic_memory(int size){
    int *ptr = calloc(1, size);
    if (ptr == NULL)
        exit(1);
    return ptr;
}


/* free the shared memory identified by args
*/
void destroy_shared_memory(char* name, void* ptr, int size){}


/* free the dynamic memory identified by args
*/
void destroy_dynamic_memory(void* ptr){
    free(ptr);
}


/*
* func that writes a operation in shared memory buffer (main & clients)
* op. should be on a free buffer space. no space? write nothing.
* be careful of buffer type + buffer writing rules.
*/
void write_main_client_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op){}


/* 
* func that writes a operation in shared memory buffer (clients & intermediaries)
* op. should be on a free buffer space. no space? write nothing.
* be careful of buffer type + buffer writing rules.
*/
void write_client_interm_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op){}


/* 
* func that
* func that writes a operation in shared memory buffer (intermediaries & companies)
* op. should be on a free buffer space. no space? write nothing.
* be careful of buffer type + buffer writing rules.
*/
void write_interm_enterp_buffer(struct rnd_access_buffer* buffer, int buffer_size, struct operation* op){}


/*
* func that reads an operation in shared memory operation between Main & clients, if
* there was an available buffer directed to a specific client 
* careful about buffer type and rules for reading into buffers
* if theres no operation avaiable put op->id = -1.
*/
void read_main_client_buffer(struct rnd_access_buffer* buffer, int client_id, int buffer_size, struct operation* op){}


/* 
* func that reads an operation in a shared memory operation between clients & intermediaries, if
* there was an to read (all intermd. could read any op.)
* careful about buffer type and rules for reading into buffers
* if theres no operation avaiable put op->id = -1.
*/
void read_client_interm_buffer(struct circular_buffer* buffer, int buffer_size, struct operation* op){}

/* 
* func that reads an operation in a shared memory operation between intermediaries & companies, if
* there was an to read directed to a specific company.
* careful about buffer type and rules for reading into buffers
* if theres no operation avaiable put op->id = -1.
*/
void read_interm_enterp_buffer(struct rnd_access_buffer* buffer, int enterp_id, int buffer_size, struct operation* op){}
