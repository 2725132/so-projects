/*
        Felipe Gouvêa, 92399
		Henrique Haji, 92413

		Algoritmo Next Fit
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
    TApontador UltimoPesquisado;
    int QuantidadeDeProcessos;
}TLista;

TNo *Cria(int tamanho, int code){
    TNo *novo = (TApontador)malloc(sizeof(TNo));
    novo->prox = NULL;
    novo->tam = tamanho;
    novo->disp = NAO;
	novo->code = code;
    return novo;
}
int Insere(TLista *lista, int tamanho){
    int cont = 0;
    TNo *aux = Cria(tamanho, lista->QuantidadeDeProcessos);
   if(lista->Inicio == NULL){
   		aux->code = -2;
        lista->Inicio = aux;
        lista->Fim = lista->Inicio;
        lista->UltimoPesquisado = lista->Inicio;
        lista->QuantidadeDeProcessos++;
        return 1;

	}else{
        //ALOCA PROCESSO PARA MEMÓRIA JÁ DISPONVEL
        TNo *aux2 = lista->UltimoPesquisado;

        while(cont < lista->QuantidadeDeProcessos){
            if(aux2->disp == SIM){
                if(aux->tam <= aux2->tam){
      				aux->disp = SIM;
	                aux->tam = aux2->tam - tamanho;
					aux->prox = aux2->prox;
                    aux2->prox = aux;

					aux2->code = lista->QuantidadeDeProcessos;
                    aux2->disp = NAO;
                    aux2->tam = tamanho;

					lista->UltimoPesquisado = aux2;
					//lista->Inicio->tam-= tamanho;
                    printf("Inseriu %d \n", tamanho);

					lista->QuantidadeDeProcessos++;
					return 1;
                }
            }
            cont++;
            aux2 = aux2->prox;
        }
            //Chegou ao fim da lista
            if(aux->tam <= lista->Inicio->tam){
                lista->Fim->prox = aux;
                aux->prox = lista->Inicio;
                lista->Inicio->tam -= aux->tam;
                lista->Fim = aux;

                lista->QuantidadeDeProcessos++;
                printf("Inseriu %d \n", tamanho);
                return 1;

			}

    }
    printf("Nao ha memoria suficiente para alocar um processo de tamanho %d\n", tamanho);
    return 0;
}

void ConsertaMemoria(TLista *lista){
    int cont = 0;
	TNo *aux = lista->Inicio;
	if(aux == NULL) return;
	while(cont < lista->QuantidadeDeProcessos){
		if(aux->disp == SIM && aux->prox->disp == SIM){
			aux->tam += aux->prox->tam;

			TNo *aux2 = aux->prox;
			aux->prox = aux->prox->prox;
			free(aux2);
			return;
		}
		cont++;
		aux = aux->prox;
	}
}

int Remove(TLista *lista, int code){
	TNo *aux = lista->UltimoPesquisado;
	TNo *aux2;
	int cont = 0;
	if(lista->Inicio == NULL) return -1;
	while(cont < lista->QuantidadeDeProcessos){
		if(aux->prox->code == code){
			aux->prox->disp = SIM;
			aux->prox->code = -1;
			lista->UltimoPesquisado = aux->prox;
			printf("Removeu %d\n", code);
			ConsertaMemoria(&(*lista));
			return 1;
		}
		cont++;
		aux = aux->prox;
	}
	printf("O codigo %d nao existe nao esta alocado\n", code);
	return 0;
}

void ImprimeAlocado(TLista *lista){
	TNo *aux = lista->Inicio->prox;
	int cont = 1;

	printf("\nTamanho de memoria disponivel %d\n", lista->Inicio->tam);
	while(aux != lista->Inicio){
		if(aux == NULL) return;
		if(aux->disp == NAO) printf("Codigo %d   Tamanho [%d]\n ", aux->code, aux->tam);
		else printf("Codigo %d   Tamanho %d\n ", aux->code, aux->tam);

		aux = aux->prox;
		cont++;
	}
	printf("\n");
}

void InicializaLista(TLista *lista){
	lista->Fim = NULL;
	lista->Inicio = NULL;
	lista->UltimoPesquisado = NULL;
	lista->QuantidadeDeProcessos = 0;
}
int main(void){
        int qtd_num;
        int tam;
        TLista T;
        InicializaLista(&T);
		//scanf("%d", &tam);
		int num;
		int i;
        tam = 10;
        printf("Insira o tamanho total da memória desejada: ");
		scanf("%d", &tam);
		Insere(&T, tam);
		printf("\n");


		printf("Insira a quantidade de processos de tamanho aleatório desejada: ");
		scanf("%d", &qtd_num);
		printf("\n");
		srand(time(NULL));

		for(i = 0; i < qtd_num ; i++){
			num = 1 + (rand() / tam);
			//scanf("%d", &num);
			Insere(&T, num);

			//Remove(&T, num);
			//ImprimeAlocado(&T);
		}

		ImprimeAlocado(&T);

		Remove(&T, 3);
		ImprimeAlocado(&T);
        /*
		Remove(&T, 4);
		ImprimeAlocado(&T);

		Remove(&T, 5);
		ImprimeAlocado(&T);
        */



		Insere(&T, 1);
		ImprimeAlocado(&T);


        return 0;
    }
