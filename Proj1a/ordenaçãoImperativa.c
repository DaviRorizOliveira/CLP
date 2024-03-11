#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100
#define REPETICOES 1024

void insertionSort(int arr[], int tamanho) {
    int i, j, aux;
    for (i = 1 ; i < tamanho ; i++) {
        aux = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > aux) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = aux;
    }
}

void geradorDeVetor(int arr[], int tamanho) {
    for (int i = 0 ; i < tamanho ; i++) {
        arr[i] = rand() % 1000;
    }
}

int main(void) {
    srand(time(NULL));

    FILE *arquivo;
    arquivo = fopen("resultadosEmC.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    for (int a = 0 ; a < REPETICOES ; a++) {
        clock_t inicio = clock();
        int vetor[TAM];
        
        for (int i = 0 ; i < REPETICOES ; i++) {
            geradorDeVetor(vetor, TAM);
            insertionSort(vetor, TAM);
        }
        clock_t fim = clock();
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        fprintf(arquivo, "%.3f\n", tempo);
    }
    fclose(arquivo);

    return 0;
}