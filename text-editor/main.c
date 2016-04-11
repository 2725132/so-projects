#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define max_line 4
#define N 10000
pthread_mutex_t lock_buffer;
char buffer[N];
sem_t vazio; // <- N
sem_t cheio; // <- 0
int in = 0,  //posicao p/ inserir no buffer itens
    out= 0;  //posicao p/ remover do buffer itens

void *processador() {

	while (1) {
		sem_wait(&cheio);
		//pthread_mutex_lock(&lock_buffer);
        processar();
        fflush(stdout);
        imprime_buffer();
		//pthread_mutex_unlock(&lock_buffer);
		sem_post(&vazio);
	}
}

void processar(){
    int n = 4;
    /// n = 4
    printf("Processando dados....\n");
    int m = in;
    char *temp = (char*)malloc(m*sizeof(char));
    strcpy(temp,buffer);
    strcpy(buffer,"");
    in = 0;

    if(m > max_line){
        int teto = m/max_line;
        printf("M MAIOR QUE N  %d\n", teto);
    }


    printf("String copiada %s\n", temp);
    //exit(EXIT_SUCCESS);
}

void *leitor() {
	int item, i=0;

	while (1) {
		sem_wait(&vazio);
		//pthread_mutex_lock(&lock_buffer);
		le_string();
		fflush(stdout);
        printf("\nTerminou de ler\n");
        imprime_buffer();
		//pthread_mutex_unlock(&lock_buffer);
		sem_post(&cheio);
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
        printf("BUFFER = %s, IN = %d\n", buffer, in);
}


int main()
{
    sem_init(&vazio, 0 , N);
    sem_init(&cheio, 0 , 0);
    pthread_t t_leitor;
    pthread_t t_processador;

    pthread_create(&t_leitor, NULL, leitor, NULL);
    pthread_create(&t_processador, NULL, processador, NULL);

    pthread_join(t_leitor, NULL);
    pthread_join(t_processador, NULL);
    return 0;
}
