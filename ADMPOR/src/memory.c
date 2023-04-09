/*
 * Emily Sá          fc58200
 * Yichen Cao "Mimi" fc58165
 * Gonçalo Fernandes fc58194
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
#include "memory-private.h"


/*
 * reserves a shared memory zone with <size> & <name>. fill the zone with 0
 * return pointer. concatenate the result using func getuid()
 * to make the name unique to the process.
 */
void *create_shared_memory(char *name, int size)
{
    char* legalName = malloc(strlen(name) + 2);
    legalName[0] = '/'; 
    legalName[1] = '\0';
    strcpy(&legalName[1], name);

    int *ptr;
    int ret;
    int fd = shm_open(legalName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror(legalName);
        exit(1);
    }

    ret = ftruncate(fd, size);
    if (ret == -1)
    {
        perror(legalName);
        exit(2);
    }

    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror(legalName);
        perror("-mmap");
        exit(3);
    }
    return ptr;
}

/*
 * func that reserves a dynamic space of size. fill the zone with 0
 * return pointer
 */
void *create_dynamic_memory(int size)
{
    int *ptr = calloc(1, size);
    if (ptr == NULL)
        exit(1);
    return ptr;
}

/* free the shared memory identified by args
 */
void destroy_shared_memory(char *name, void *ptr, int size)
{
    int ret;
    ret = munmap(ptr, size);
    if (ret == -1)
    {
        perror(name);
        exit(7);
    }

    ret = shm_unlink(name);
    if (ret == -1)
    {
        perror(name);
        exit(8);
    }
}

/* free the dynamic memory identified by args
 */
void destroy_dynamic_memory(void *ptr)
{
    free(ptr);
}

/*
 * func that writes a operation in shared memory buffer (main & clients)
 * op. should be on a free buffer space. no space? write nothing.
 * be careful of buffer type + buffer writing rules.
 */
void write_main_client_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op)
{
    write_rnd_access_buffer(buffer, buffer_size, op);
}

/*
 * func that writes a operation in shared memory buffer (clients & intermediaries)
 * op. should be on a free buffer space. no space? write nothing.
 * be careful of buffer type + buffer writing rules.
 */
void write_client_interm_buffer(struct circular_buffer *buffer, int buffer_size, struct operation *op)
{
    struct pointers *p = buffer->ptrs;
    int in = p->in;
    int out = p->in;
    struct operation *ops = buffer->buffer;

    if (((in + 1) % buffer_size) != out)
    {
        *(ops + in) = *op;
        in = (in + 1) % buffer_size;
    }
}

/*
 * func that
 * func that writes a operation in shared memory buffer (intermediaries & companies)
 * op. should be on a free buffer space. no space? write nothing.
 * be careful of buffer type + buffer writing rules.
 */
void write_interm_enterp_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op)
{
    write_rnd_access_buffer(buffer, buffer_size, op);
}

/*
 * func that reads an operation in shared memory operation between Main & clients, if
 * there was an available buffer directed to a specific client
 * careful about buffer type and rules for reading into buffers
 * if theres no operation avaiable put op->id = -1.
 */
void read_main_client_buffer(struct rnd_access_buffer *buffer, int client_id, int buffer_size, struct operation *op)
{
    read_rnd_access_buffer(buffer, buffer_size, client_id, op);
}

/*
 * func that reads an operation in a shared memory operation between clients & intermediaries, if
 * there was an to read (all intermd. could read any op.)
 * careful about buffer type and rules for reading into buffers
 * if theres no operation avaiable put op->id = -1.
 */
void read_client_interm_buffer(struct circular_buffer *buffer, int buffer_size, struct operation *op)
{
    struct pointers *p = buffer->ptrs;
    int in = p->in;
    int out = p->in;
    struct operation *ops = buffer->buffer;

    if (in == out)
    {
        op->id = -1;
    }
    else
    {
        *op = *(ops + out);
        out = (out + 1) % buffer_size;
    }
}

/*
 * func that reads an operation in a shared memory operation between intermediaries & companies, if
 * there was an to read directed to a specific company.
 * careful about buffer type and rules for reading into buffers
 * if theres no operation avaiable put op->id = -1.
 */
void read_interm_enterp_buffer(struct rnd_access_buffer *buffer, int enterp_id, int buffer_size, struct operation *op)
{
    read_rnd_access_buffer(buffer, buffer_size, enterp_id, op);
}

void write_rnd_access_buffer(struct rnd_access_buffer *buffer, int buffer_size, struct operation *op)
{
    int *p = buffer->ptrs;
    struct operation *ops = buffer->buffer;
    for (int i = 0; i < buffer_size; i++)
    {
        if (*(p + i) == 0)
        {
            *(p + i) = 1;
            *(ops + i) = *op;
            break;
        }
    }
}

void read_rnd_access_buffer(struct rnd_access_buffer *buffer, int id, int buffer_size, struct operation *op)
{
    int found = 0;
    int *p = buffer->ptrs;
    struct operation *ops = buffer->buffer;
    for (int i = 0; i < buffer_size; i++)
    {
        if (*(p + i) == 1 && (ops + i)->id == id)
        {
            *op = *(ops + i);
            *(p + i) = 0;
            found = 1;
            break;
        }
    }
    if (!found)
    {
        op->id = -1;
    }
}