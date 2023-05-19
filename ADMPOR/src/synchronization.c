#include <semaphore.h>
#include <fcntl.h> 
#include <synchronization.h>  

/* Função que cria um novo semáforo com nome name e valor inicial igual a
* value. Pode concatenar o resultado da função getuid() a name, para tornar
* o nome único para o processo.
*/
sem_t * semaphore_create(char* name, int value){
    sem_open(name, O_CREAT, 0xFFFFFFFF,value);

}

/* Função que destroi o semáforo passado em argumento.
*/
void semaphore_destroy(char* name, sem_t* semaphore){

    int r1 = sem_close(semaphore);
    int r2 = sem_unlink(name);
    
    if(r1 == -1){
        "Closing semaphores failed.\n";
    }
    if(r2== -1){
        "Unlinking semaphores failed.\n";
    }
}

/* Função que inicia o processo de produzir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_begin(struct prodcons* pc){
    semaphore_mutex_lock(pc->empty);
    semaphore_mutex_lock(pc->mutex);
}

/* Função que termina o processo de produzir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void produce_end(struct prodcons* pc){
    semaphore_mutex_unlock(pc->mutex);
    semaphore_mutex_unlock(pc->full);
}

/* Função que inicia o processo de consumir, fazendo sem_wait nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_begin(struct prodcons* pc){
    semaphore_mutex_lock(pc->full);
    semaphore_mutex_lock(pc->mutex);
}

/* Função que termina o processo de consumir, fazendo sem_post nos semáforos
* corretos da estrutura passada em argumento.
*/
void consume_end(struct prodcons* pc){
    semaphore_mutex_unlock(pc->mutex);
    semaphore_mutex_unlock(pc->empty);
}

/* Função que faz wait a um semáforo.
*/
void semaphore_mutex_lock(sem_t* sem){
    sem_wait(sem);
}

/* Função que faz post a um semáforo.
*/
void semaphore_mutex_unlock(sem_t* sem){
    sem_post(sem);
}