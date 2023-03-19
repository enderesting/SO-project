#include <stdio.h>
#include "memory.h"
#include "main.h"
 
/* Função que inicia um novo processo cliente através da função fork do SO. O novo
* processo irá executar a função execute_client respetiva, fazendo exit do retorno.
* O processo pai devolve o pid do processo criado.

* function that creates a new client process through function SO fork()
* new process will execute its respective execute_client, making exit return (fazendo exit do retorno?)
* parent process gets(devolve?) pid of child process
*/
int launch_client(int client_id, struct comm_buffers* buffers, struct main_data* data){}


/*
* function that creates a new client process through function SO fork()
* new process will execute its respective execute_intermediary, making exit return
* parent process gets(devolve?) pid of child process
*/
int launch_interm(int interm_id, struct comm_buffers* buffers, struct main_data* data){}


/*
* function that creates a new client process through function SO fork()
* new process will execute its respective execute_enterprise, making exit return
* parent process gets(devolve?) pid of child process
*/
int launch_enterp(int enterp_id, struct comm_buffers* buffers, struct main_data* data){}


/* 
* Func that waits until a process is terminated through waitpid()
* returns the process back (Devolve o retorno do processo???) once normally ended
*/
int wait_process(int process_id){}