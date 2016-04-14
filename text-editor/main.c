#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define max_line 42
#define N 10000000
pthread_mutex_t lock_buffer;
char buffer[N];
sem_t vazio; // <- N
sem_t cheio; // <- 0
int in = 0,  //posicao p/ inserir no buffer itens
    out= 0;  //posicao p/ remover do buffer itens
long int it;
void *processador() {

	while (1) {
		sem_wait(&cheio);
		pthread_mutex_lock(&lock_buffer);
        processar();
        fflush(stdout);
		pthread_mutex_unlock(&lock_buffer);
		sem_post(&vazio);
		//imprime_buffer();
	}
}

void processar(){
    int n = 4;
    /// n = 4
    //imprime_buffer();
    printf("Processando dados....\n");
    int m = in;
    char *temp = (char*)malloc(m*sizeof(char));
    char *temp2 = (char*)malloc(m*sizeof(char));
    strcpy(temp,buffer);
    strcpy(buffer,"");
    in = 0;

    if(m > max_line){
        int teto = m/max_line;
        //printf("M MAIOR QUE N  %d\n", teto);
    }
    int i,j;
    for ( i = 0, j = 1; i < m; i++,j++){
        if(i == max_line) {
            temp2[i] = '\n';
            j--;
        }
        else if(temp[j] ){
            temp2[i] = temp[j];
             }// printf("erro");

    }
    strcpy(buffer,temp2);
    //strcpy(buffer,temp);
    imprime_buffer();
    //printf("String copiada %s\n", temp);
    //exit(EXIT_SUCCESS);
}
char * le_string(){

    //printf("Lendo entrada\n");
    char * entrada = (char*)malloc(sizeof(char));
    it = 1;
    entrada[0] = '!';

    while(1){
        scanf("%c", &entrada[it]);
        if(entrada[it-1] == '.')break;
        in = (in + 1) % N;
        it++;
    }


    /* FUNÇÃO DE TESTE
    while(it<=1) {
        entrada[it] = '1';
        it++;
        in = (in + 1) % N;
        //usleep(1000000);
    }
    */
    return entrada;
}
void *leitor() {

    char * entrada;

	while (1) {

        entrada = le_string();
		sem_wait(&vazio);
		//printf("Lendo..\n");
		pthread_mutex_lock(&lock_buffer);

        memcpy(buffer, entrada, it);
        fflush(stdout);

		pthread_mutex_unlock(&lock_buffer);
		sem_post(&cheio);

        //printf("\nTerminou de ler\n");
        //imprime_buffer();
	}
}


void imprime_buffer(){
        printf("%s\n", buffer, in);
}


int main()
{
    sem_init(&vazio, 0 , 1);
    sem_init(&cheio, 0 , 0);
    pthread_t t_leitor;
    pthread_t t_processador;

    pthread_create(&t_leitor, NULL, leitor, NULL);
    pthread_create(&t_processador, NULL, processador, NULL);

    pthread_join(t_leitor, NULL);
    pthread_join(t_processador, NULL);
    return 0;
}
