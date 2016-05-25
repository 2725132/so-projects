/*
        Felipe Gouvêa, 92399
		Henrique Haji, 92413


		Funcionamento:
			Digite o tamanho da memória total a ser alocada, ela terá código -2
			Digite a quantidade de processos a serem alocados, o código será de acordo com a quantidade total, o primeiro terá código 1, o segundo código 2 e assim por diante
			Pedaços de memória em que processos não estão alocados, irão possuir código -1

*/
    #include <stdio.h>
#define SIM 1
#define NAO 0
typedef int TChave;
typedef struct{
    TChave Chave;
} TItem;

typedef struct SNo *TApontador;
typedef struct SNo{
    int tam;
    int code;
    int disp;
    TApontador ant, prox;
} TNo;

typedef struct{
    TApontador Inicio, Fim;
}TLista;
int Insere(TLista *lista, int tamanho, int code){
    TNo *aux = (TNo*)malloc(sizeof(TNo));
    //aux->mem = 0;
    aux->tam = tamanho;
    aux->disp = NAO;
    aux->code = code;

    aux->prox = NULL;
    aux->ant = NULL;
    if(lista->Inicio == NULL){
        lista->Inicio = aux;
        return 1;
    }else{
        //ALOCA PROCESSO PARA MEMÓRIA JÁ DISPONVEL
        TNo *aux2 = lista->Inicio;
        while(aux2->prox != NULL){
            if(aux2->disp == SIM){
                if(aux->tam <= aux2->tam){
      				aux->disp = SIM;
	                aux->tam = aux2->tam - tamanho;
					aux->prox = aux2->prox;
                    aux2->prox = aux;



					aux2->code = tamanho;
                    aux2->disp = NAO;
                    aux2->tam = tamanho;

					//lista->Inicio->tam-= tamanho;
                    printf("Inseriu %d \n", tamanho);
					return 1;
                }
            }
            aux2 = aux2->prox;
        }
        if(aux->tam < lista->Inicio->tam){
        	aux2->prox = aux;
			lista->Inicio->tam -= tamanho;
			printf("Inseriu %d \n", tamanho);
			return 1;
		}

    }
    printf("Nao ha memoria suficiente para alocar um processo de tamanho %d\n1", tamanho);
    return 0;
}
void ConsertaMemoria(TLista *lista){
	TNo *aux = lista->Inicio;
	if(aux == NULL) return;
	while(aux->prox != NULL){
		if(aux->disp == SIM && aux->prox->disp == SIM){
			aux->tam += aux->prox->tam;

			TNo *aux2 = aux->prox;
			aux->prox = aux->prox->prox;
			free(aux2);
			return;
		}
		//printf("erro\n");
		aux = aux->prox;
	}
}
int Remove(TLista *lista, int code){
	TNo *aux = lista->Inicio;
	TNo *aux2;
	while(aux->prox != NULL){
		if(aux->prox->code == code){
			aux->prox->disp = SIM;
			aux->prox->code = -1;
			printf("Removeu %d\n", code);
			ConsertaMemoria(&(*lista));
			return 1;
		}
		aux = aux->prox;
	}
	printf("O codigo %d nao existe nao esta alocado\n", code);
	return 0;
}

void ImprimeAlocado(TLista *lista){
	TNo *aux = lista->Inicio;
	while(aux != NULL){
		if(aux->disp == NAO) printf("Codigo %d   Tamanho [%d]\n ", aux->code, aux->tam);
		else printf("Codigo %d   Tamanho %d\n ", aux->code, aux->tam);
		aux = aux->prox;
	}
	printf("\n");
}
int main(void){
        int qtd_num;
        int tam;
        TLista T;
        T.Inicio = NULL;
        T.Fim = NULL;
		//scanf("%d", &tam);
		int num;
		int i;
        tam = 10;
        printf("Insira o tamanho total da memória desejada: ");
		scanf("%d", &tam);
		Insere(&T, tam, -2);
		printf("\n");


		printf("Insira a quantidade de processos de tamanho aleatório desejada: ");
		scanf("%d", &qtd_num);
		printf("\n");
		srand(time(NULL));

		for(i = 0; i < qtd_num ; i++){
			num = 1 + (rand() / tam);
			//scanf("%d", &num);
			Insere(&T, num, i);

			//Remove(&T, num);
			//ImprimeAlocado(&T);
		}
		ImprimeAlocado(&T);

		Remove(&T, 1);
		ImprimeAlocado(&T);

		Insere(&T, 500, 1);
		ImprimeAlocado(&T);
		/*
		Remove(&T, 1);
		ImprimeAlocado(&T);
		Remove(&T, 2);
		ImprimeAlocado(&T);
		//Remove(&T, 2);
		//Remove(&T, 3);
		//Insere(&T, 1);

        //printf("%d", tab->Item[0].Chave);
        */
        return 0;
    }
