#include <stdio.h>
#include <stdlib.h>
#define MAX_COM 256
void print_mat_char(char **mat, int l){
	int i;
	for (i=0; i<l; i++)
		printf("%s\n", mat[i]);
}

char **alloc_2d_char(int l, int c) {
	char **mat=NULL;
	int i;
	mat = (char **)calloc(l, sizeof(char *));
	if (!mat) {
		perror("mat = calloc()");
		return NULL;
	}
	for (i=0; i<l; i++) {
		mat[i] = (char *)calloc(c, sizeof(char));
		if (!mat[i]) {
			perror("mat[i] = calloc()");
			return NULL;
		}
	}
	return mat;
}

int *read_command(char *command, char **parameters) {
	int i, ip, jp;
	int resp[2] = {1 , 0};
	char str[MAX_COM];
	fgets(str, MAX_COM, stdin);
	i=0; ip=0; jp=0;



	while (str[i] != '\n'){
		while (str[i] == ' ') i++;
            if(ip == 0){
                strcat(parameters[ip], "/bin/");
                jp = 5;
            }
            while(str[i] == ' ') i--;
            if(str[i] == '|'){
                strcat(parameters[ip], "/bin/");
                jp = 5;
            }
		while (str[i] != ' ' && str[i] != '\n') {
			if(str[i] == '|'){
				resp[1] += 1;
            }
			parameters[ip][jp] = str[i];

			i++; jp++;
		}
		resp[0]++;
        jp=0,ip++;
	}


    //printf("%s", parameters[0]);
    parameters[ip] = NULL;

	resp[0] = ip;

	return(resp);
}

void type_prompt(void) {
	printf("COMEÇAL> ");
}

int executa_comando(char **cmd, int ind){

    int indice_comeco;

    if (ind <= 0){
        return ind;
    }

    else {
        int indice = ind;
        int i;
        //printf("%s", cmd[indice]);
        indice--;
        indice_comeco = executa_comando(cmd, indice);
    }

    if(cmd[indice_comeco][0] == '|') return indice_comeco;
    if(cmd[indice_comeco][0] == '-') return indice_comeco;
    if(cmd[indice_comeco][0] == NULL) return indice_comeco;

    char **command = alloc_2d_char(50,100);

    int i = 0;

    while(cmd[indice_comeco] != NULL){
            if(cmd[indice_comeco][0] == '|') break;
            command[i] = cmd[indice_comeco];
            i++;
            indice_comeco++;
        }
        command[i+1] = NULL;

        int j = 0;
        while(command[j][0] != NULL) {
            printf("%s\n", command[j]);
            j++;

        }

        printf("------\n");
        return indice_comeco+1;

}


void inicializa(){
	int *na = {0,0}; //quantidade de argumentos do comando
	char **parameters;
	char *command;
	while(1){
        type_prompt();
        parameters = alloc_2d_char(50, 100);
		// 50 argumentos, cada argumento 100 caracteres
        na = read_command(command, parameters);

        //printf("numero de linhas %d\n", na[0]);
        //printf("parameters[0] = %s\n", parameters[0]);
        int i = 0;
        while(parameters[i] != NULL){
            printf("%s\n", parameters[i]);
            i++;
        }

        //executa_comando(parameters, na[0]);

        //printf("%d",executa_comando(parameters, na[0]-1) );
    }
}



int main()
{
    inicializa();
    return 0;
}
