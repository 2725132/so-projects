#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10000
pthread_mutex_t lock_in;
pthread_mutex_t lock_out;
char buffer[N];
sem_t vazio; // <- N
sem_t cheio; // <- 0
int in = 0,  //posicao p/ inserir no buffer itens
    out= 0;  //posicao p/ remover do buffer itens

void produtor(void *args) {
	int item, i=0;

	while (1) {
//		sem_wait(&vazio);
		//pthread_mutex_lock(&lock_in);
		le_string();
		fflush(stdout);
        printf("Terminou de ler\n");
        imprime_buffer();
		//pthread_mutex_unlock(&lock_in);
//		sem_post(&cheio);
	}
}

void le_string(){
    printf("Lendo entrada\n");
    while(1){
        scanf("%c", &buffer[in]);
        if(buffer[in] == '-')return;
        in = (in + 1) % N;
    }

}

void imprime_buffer(){
        printf("BUFFER = %s", buffer);
}


int main()
{
    produtor(NULL);
    return 0;
}
