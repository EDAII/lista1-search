/*
    Djorkaeff Alexandre Vilela Pereira - 16/0026822
    Guilherme Siqueira Brandão - 16/0007763 
*/
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define REPEATED 1
#define NREPEATED 0
#define GNUPLOT "gnuplot -persist"

void generateVector(int tam, int *matriz);
int searchValue(int value, int *matriz, int tam);
void swap(int *matriz, int a, int b);

int main()
{
	int tam, value, index, *matriz = NULL;
    FILE *gp;
    gp = popen(GNUPLOT, "w");
    if (gp == NULL) {
        printf("Erro ao abrir pipe para o GNU plot.\n"
            "Instale com 'sudo apt-get install gnuplot'\n");
        exit(0);
    }

    FILE *fp;
    fp = fopen("dados.txt", "w+");

	printf("Tamanho do vetor gerado: ");
	scanf("%i", &tam);

	matriz = (int *)malloc(tam+1 * sizeof(int));

    generateVector(tam, matriz);

    do {
        printf("\nValor a ser procurado (ou 0 para terminar): ");
	    scanf("%i", &value);

        // Add sentinel
        matriz[tam] = value;

        srand(0);
        clock_t t;
        t = clock();
        index = searchValue(value, matriz, tam);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        if(value!=0) {
            if(index==tam) {
                printf("\n%d não está presente no vetor.\n", value);
            } else {
                printf("\n%d é a posição do vetor em que o valor %d se encontra.\n", index, value);
                fprintf(fp, "%lf\t%d\n",t, index);
            }
            printf("\nExecutado em %lf (s)..\n",time_taken);
        }
    } while(value!=0);
    fprintf(gp, "plot 'dados.txt'\n");
	return 0;
}

void generateVector(int tam, int *matriz) {
    int numSorteado;
    int vetor[tam]/* = {tam+1}*/;
    int status;
    srand(time(NULL));
	for (int i = 0; i < tam; i++)
	{
        do
        {
            numSorteado = ((rand() % tam + 1));
            status = NREPEATED;
            for(int aux = 0; aux < tam; aux++)
            {
                if(numSorteado == vetor[aux])
                    status = REPEATED;
            }
        }while(status == REPEATED);
        vetor[i] = numSorteado;
        matriz[i] = vetor[i];
        
		//matriz[i] = rand() % tam + 1;
	}
}

int searchValue(int value, int *matriz, int tam) {
    int count, index, i;
    for(count=0; count<=tam; count++) {
        if(matriz[count]==value) {
            index = count;
            i = count;
            // Transposition method
            swap(matriz, index, index-1);
            return i;
        }
    }

    return i;
}

void swap(int *matriz, int a, int b) {
    int aux;

    if(a==0) return;

    aux = matriz[a];
    matriz[a] = matriz[b];
    matriz[b] = aux;
}
