/*
 * Grupo: SO-001
 * José "Emily" Sá   fc58200
 * Yichen Cao "Mimi" fc58165
 * Gonçalo Fernandes fc58194
 */
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "main.h"
#include "process.h"
#include <unistd.h>




/*
* reads app args (max operations, shared buffer size,
* num of client + intermediates + companies). keep in main_data
*/
void main_args(int argc, char* argv[], struct main_data* data) {
    if (argc == 6){
        data->max_ops = atoi(argv[1]);
        data->buffers_size = atoi(argv[2]);
        data->n_clients =  atoi(argv[3]);
        data->n_intermediaries = atoi(argv[4]);
        data->n_enterprises = atoi(argv[5]);
    }else{
        printf("Incorrect number of arguments. please run the program with the following args: \n");
        printf("$./AdmPor max_ops buffers_size n_clients n_intermediaries n_enterprises\n");
        printf("max_ops          - max number of operations\n");
        printf("buffers_size     - max size of buffer\n");
        printf("n_clients        - max number of clients\n");
        printf("n_intermediaries - max number of intermediaries\n");
        printf("n_enterprises    - max number of enterpreises\n\n");
        exit(1);
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
    size_t opSize = sizeof(struct operation);
    buffers->main_client->buffer = create_shared_memory(STR_SHM_MAIN_CLIENT_BUFFER, buffSize*opSize);
    buffers->client_interm->buffer = create_shared_memory(STR_SHM_CLIENT_INTERM_BUFFER, buffSize*opSize);
    buffers->interm_enterp->buffer = create_shared_memory(STR_SHM_INTERM_ENTERP_BUFFER, buffSize*opSize);

    //ptrs -> pointing at every element
    size_t intSize = sizeof(int);
    buffers->main_client->ptrs = create_shared_memory(STR_SHM_MAIN_CLIENT_PTR, buffSize*intSize);
    buffers->client_interm->ptrs = create_shared_memory(STR_SHM_CLIENT_INTERM_PTR, buffSize*sizeof(struct pointers));
    buffers->interm_enterp->ptrs = create_shared_memory(STR_SHM_INTERM_ENTERP_PTR, buffSize*intSize);

    // point their actual ptrs at the beginning too?
    data->results = create_shared_memory(STR_SHM_RESULTS, MAX_RESULTS*opSize);
    data->terminate = create_shared_memory(STR_SHM_TERMINATE,sizeof(int));
}

/*
* func that iniciates client/interm/company processes. you can use launch_*
* store the pids in its respective arrays in data structure
*/
void launch_processes(struct comm_buffers* buffers, struct main_data* data){
    for(int i = 0; i<(data->n_clients); i++){
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
    int check = 1;
    int* op_counter = calloc(1,sizeof(int));
    printf("Ações disponíveis:\n");
        printf("        op cliente empresa - criar uma nova operação\n");
        printf("        status id - consultar o estado de uma operação\n");
        printf("        stop - terminar a execução do AdmPor\n");
        printf("        help - imprime informação sobre as ações disponíveis\n");
    while(check == 1){
        // reads user input
        printf("Introduzir ação:\n");
        // char cmd[30];
        char *cmd = malloc(30*sizeof(char));
        scanf("%s",cmd);
        
        if(strcmp(cmd,"op")==0){ //also a pointer
            create_request(op_counter,buffers,data); // supposed to be a pointer
        }else if(strcmp(cmd,"status")==0){
            read_status(data);
        }else if(strcmp(cmd,"stop")==0){
            stop_execution(data,buffers);
            check = 0;
        }else if(strcmp(cmd,"help") == 0){
            printf("Ações disponíveis:\n");
            printf("        op cliente empresa - criar uma nova operação\n");
            printf("        status id - consultar o estado de uma operação\n");
            printf("        stop - terminar a execução do AdmPor\n");
            printf("        help - imprime informação sobre as ações disponíveis\n");
        }else{
            //command invalid! enter "help" to get help
            printf("Ação não reconhecida, insira 'help' para assistência.\n");
        }
        sleep(1);
    }
    free(op_counter);
}

/*
* creates a operation, defined by op_counter and data introduced in command line
* write op in the memory buffer shared between main and clients. print operation ip and op_counter++
* never create more opertation than the size of array data->results.
*/
void create_request(int* op_counter, struct comm_buffers* buffers, struct main_data* data){
    int opCount = *op_counter;
    int client,empresa;
    scanf(" %d %d", &client, &empresa);
    if(opCount<(data->max_ops)){
        //create op
        struct operation *op_ptr = calloc(1,sizeof(struct operation));
        op_ptr->id = opCount;
        op_ptr->requesting_client = client;
        op_ptr->requested_enterp = empresa;
        op_ptr->status = 'M';
        op_ptr->receiving_client = -1;
        op_ptr->receiving_interm = -1;
        op_ptr->receiving_enterp = -1;

        //write in main-client buffer
        write_main_client_buffer(buffers->main_client,data->buffers_size,op_ptr); // happens right after here
        printf("O pedido #%d foi criado!\n",opCount);
        *op_counter = opCount+1;
        // op_counter_pointer
        free(op_ptr);
    }else{
        printf("O número máximo dee operação já foi atingido.\n");
        stop_execution(data,buffers);
    }
}

/*
* func that reads operation id, user and see if its valid
* yes -> print same info: state, cliente id, company requested, 
* client interm company id that received and processed
* no -> ??????
*/
void read_status(struct main_data* data){
    int id;
    scanf("%d", &id);

    // printf("%c\n", data->results[id].status);  
    if(data->results[id].status == '\0') {

        //printf("%c\n", data->results[id].status);
        //printf("%d\n", data->results[id].receiving_client);
        printf("Pedido %d ainda não é válido\n", id);
    }
    else if(0<=id && id<(data->max_ops)){
        for(int i = 0; i<data->max_ops; i++){
            if(data->results[i].id == id){

                if(data->results->status == 'C'){
                    printf("Pedido %d com estado %c requisitado pelo cliente %d à empresa %d, foi recebido pelo cliente %d!\n", 
                    id, data->results[i].status, data->results[i].requesting_client, data->results[i].requested_enterp, 
                    data->results[i].receiving_client);
                }
                else if(data->results[i].status == 'I'){
                    printf("Pedido %d com estado %c requisitado pelo cliente %d à empresa %d, foi recebido pelo cliente %d e pelo intermediário %d!\n", 
                    id, data->results[i].status, data->results[i].requesting_client, data->results[i].requested_enterp, 
                    data->results[i].receiving_client, data->results[i].receiving_interm);
                }
                else if(data->results->status == 'E'){
                    printf("Pedido %d com estado %c requisitado pelo cliente %d à empresa %d, foi recebido pelo cliente %d, pelo intermediário %d e pela empresa %d!\n", 
                    id, data->results[i].status, data->results[i].requesting_client, data->results[i].requested_enterp, 
                    data->results[i].receiving_client, data->results[i].receiving_interm, data->results[i].receiving_enterp);
                }
                break;
            }
        }
    }
}

/*
* func that stops AdmPor.
* set flag data->terminate to 1
* wait for child processes to finish. 
* write stats at end of program. free reserved shared/dynamic memory
* use other main.h aux funcs
*/
void stop_execution(struct main_data* data, struct comm_buffers* buffers){
    // printf("terminate: %d \n", *data->terminate);
    *data->terminate = 1;
    // printf("terminate: %d \n", *data->terminate);
    // printf("getting out of it"); // this is only triggered AFTER the various process printed out their thing...
    wait_processes(data);
    write_statistics(data);
    destroy_memory_buffers(data, buffers);
    exit(0);
}

/* 
* waits all processes to end, using wait_process do process.h
*/
void wait_processes(struct main_data* data){

    for(int i = 0; i < (data->n_clients); i++){

        wait_process((data->client_pids[i]));
    }
}

/*
* func that prints AdmPor final stats aka how many process processed by everyone.
*/
void write_statistics(struct main_data* data){

    printf("Terminando o AdmPor! Imprimindo estatísticas:\n");

    for(int i = 0; i < data->n_clients; i++){

        printf("Cliente %d preparou %d pedidos!\n", i, data->client_stats[i]);
    }

    for(int i = 0; i < data->n_intermediaries; i++){

        printf("Intermediário %d preparou %d pedidos!\n", i, data->intermediary_stats[i]);
    }

    for(int i = 0; i < data->n_enterprises; i++){

        printf("Empresa %d preparou %d pedidos!\n", i, data->enterprise_stats[i]);
    }
}

/*
* func that frees all buffers of dynamic/shared memory in data struct
*/
void destroy_memory_buffers(struct main_data* data, struct comm_buffers* buffers){
    
    int buffSize = data->buffers_size;
    size_t opSize = sizeof(struct operation);

    //destroying shared memory
    destroy_shared_memory(STR_SHM_INTERM_ENTERP_BUFFER, buffers->interm_enterp, buffSize*opSize);
    destroy_shared_memory(STR_SHM_CLIENT_INTERM_BUFFER, buffers->client_interm, buffSize*opSize);
    destroy_shared_memory(STR_SHM_MAIN_CLIENT_BUFFER, buffers->main_client, buffSize*opSize);

    int intSize = sizeof(int);
    destroy_shared_memory(STR_SHM_MAIN_CLIENT_PTR, buffers->main_client, buffSize*intSize);
    destroy_shared_memory(STR_SHM_CLIENT_INTERM_PTR, buffers->client_interm, buffSize*sizeof(struct pointers));
    destroy_shared_memory(STR_SHM_INTERM_ENTERP_PTR, buffers->interm_enterp, buffSize*intSize);

    destroy_shared_memory(STR_SHM_RESULTS, data->results, (data->max_ops)*opSize);
    destroy_shared_memory(STR_SHM_TERMINATE, data->terminate, intSize);

    //destroying dynamic memory
    destroy_dynamic_memory(data->client_pids);
    destroy_dynamic_memory(data->intermediary_pids);
    destroy_dynamic_memory(data->enterprise_pids);
    destroy_dynamic_memory(data->client_stats);
    destroy_dynamic_memory(data->intermediary_stats);
    destroy_dynamic_memory(data->enterprise_stats);
    printf("finished the massacre");
}



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
    destroy_dynamic_memory(buffers);
}
