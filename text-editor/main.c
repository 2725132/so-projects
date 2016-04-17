#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define max_line 30
#define N 10000000
pthread_mutex_t lock_buffer;
char buffer[N];
sem_t readytoread;
sem_t readytoprocess;
sem_t readytosave; // <- N
int in = 0,  //posicao p/ inserir no buffer itens
    out= 0;  //posicao p/ remover do buffer itens
long int it;

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
    //printf("IN = %d", in);
    int i;
    int x = n = 0;
    for ( i = 0; i <= m; i++){
        temp2[i+x] = temp[i];
        if((i+1) % max_line == 0) {
            printf("%d\n", i);
            x++;
            //printf("i = %d\n",);
            temp2[i+x] = '\n';

        }

    }
    strcpy(buffer,temp2);
    //strcpy(buffer,temp);
    imprime_buffer();
    //printf("String copiada %s\n", temp);
    //exit(EXIT_SUCCESS);
}
void inserir_espaco(int qtd){

}
char * le_string(){

    //printf("Lendo entrada\n");
    char * entrada = (char*)malloc(sizeof(char));
    it = 0;
    //entrada[0] = '!';

    while(1){
        scanf("%c", &entrada[it]);
        if(entrada[it] == '.'){
            it++;
            break;
        }
        it++;

        //printf("ERRO\n");
    }
    in = it;

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



void imprime_buffer(){
        printf("%s\n", buffer, in);
}



void *processador() {

	while (1) {
		sem_wait(&readytoprocess);
		//pthread_mutex_lock(&lock_buffer);
        processar();
        fflush(stdout);
		//pthread_mutex_unlock(&lock_buffer);
		sem_post(&readytosave);
		//imprime_buffer();
	}
}
void *leitor() {

    char * entrada;

	while (1) {

        entrada = le_string();
		sem_wait(&readytoread);
		printf("Lendo..\n");
		//pthread_mutex_lock(&lock_buffer);

        memcpy(buffer, entrada, in);
        fflush(stdout);

		//pthread_mutex_unlock(&lock_buffer);
		sem_post(&readytoprocess);

        //printf("\nTerminou de ler\n");
        //imprime_buffer();
	}
}
void *salvar(){
    FILE * file;
    while (1) {
		sem_wait(&readytosave);
        printf("Salvando...\n");
		//pthread_mutex_lock(&lock_buffer);

        file = fopen ("myfile.txt","a");
        if (file!=NULL){
            fputs (buffer, file);
            fclose (file);
        }

        fflush(stdout);
		//pthread_mutex_unlock(&lock_buffer);
		sem_post(&readytoread);
	}
}



int main()
{
    sem_init(&readytoread, 0 , 1);
    sem_init(&readytoprocess, 0 , 0);
    sem_init(&readytosave, 0 , 0);

    pthread_t t_leitor;
    pthread_t t_processador;
    pthread_t t_salvador;

    pthread_create(&t_leitor, NULL, leitor, NULL);
    pthread_create(&t_processador, NULL, processador, NULL);
    pthread_create(&t_salvador, NULL, salvar, NULL);

    pthread_join(t_leitor, NULL);
    pthread_join(t_processador, NULL);
    return 0;
}
