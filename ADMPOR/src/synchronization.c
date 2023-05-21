#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h> 
#include <synchronization.h>
#include <synchronization-private.h>
#include <errno.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* Função que cria um novo semáforo com nome name e valor inicial igual a
* value. Pode concatenar o resultado da função getuid() a name, para tornar
* o nome único para o processo.
*/
sem_t * semaphore_create(char* name, int value){
    sem_t* sem;
    // uid_t uid = getuid();
    // int length = strlen(name);
    // int new_length = length+11;
    // char* new_ptr = calloc(1,new_length*sizeof(char));
    // sprintf(new_ptr,"%s%d",name,uid);

    // sem = sem_open(new_ptr, O_CREAT, 00600, value);

    sem = sem_open(name, O_CREAT|O_EXCL, 00600, value);
    
    if(sem == SEM_FAILED){
        if(errno == EEXIST){ //already exists, close first
            sem_close(sem); //returns -1 but it works anyways??
            sem_unlink(name);
            sem = sem_open(name, O_CREAT, 00600, value); //create a new one w/ value
        }else{
            perror("sem_open");
        }
    }

    int v;
    sem_getvalue(sem,&v);
    return sem;
}

/* Função que destroi o semáforo passado em argumento.
*/
void semaphore_destroy(char* name, sem_t* semaphore){
    int r1 = sem_close(semaphore);
    int r2 = sem_unlink(name);
    if(r1 == -1){
        perror("sem_close");
    }
    if(r2 == -1){
        perror("sem_unlink");
    }
}

/* Função que inicia o processo de produzir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_begin(struct prodcons* pc){
    printf("produce begin -> ");
    semaphore_mutex_lock(pc->empty); // why does it get stuck in here????? empty should have value in ittt. :()
    semaphore_mutex_lock(pc->mutex);
    // printf("\n");
}

/* Função que termina o processo de produzir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_end(struct prodcons* pc){
    semaphore_mutex_unlock(pc->mutex);
    semaphore_mutex_unlock(pc->full);
    printf("produce end.\n");
    // printf("\n");
}

/* Função que inicia o processo de consumir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_begin(struct prodcons* pc){
    printf("consume begin -> ");
    semaphore_mutex_lock(pc->full);
    semaphore_mutex_lock(pc->mutex);
    // printf("\n");
}

/* Função que termina o processo de consumir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_end(struct prodcons* pc){
    semaphore_mutex_unlock(pc->mutex);
    semaphore_mutex_unlock(pc->empty);
    
    printf("consume end. \n");
    // printf("\n");
}

/*
*  When consumer reads the buffer without changing any content, simply release.
*/
void consume_ignore(struct prodcons* pc){
    semaphore_mutex_unlock(pc->mutex);
    semaphore_mutex_unlock(pc->full);
}

/* Função que faz wait a um semáforo.
*/
void semaphore_mutex_lock(sem_t* sem){
    // printf("locking sem ");
    // int v;
    // sem_getvalue(sem,&v);
    // printf("sem_wait: %d   pid: %d\n",v,getpid());
    sem_wait(sem);
    // sem_getvalue(sem,&v);
    // printf("sem_wait2: %d   pid: %d\n",v,getpid());
}

/* Função que faz post a um semáforo.
*/
void semaphore_mutex_unlock(sem_t* sem){
    // printf("unlocking sem ");
    // int v;
    // sem_getvalue(sem,&v);
    // printf("sem_post: %d   pid: %d\n",v,getpid());
    sem_post(sem);
    // sem_getvalue(sem,&v);
    // printf("sem_post2: %d   pid: %d\n",v,getpid());
}