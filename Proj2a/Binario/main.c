// Aluno: Davi Roriz Oliveira
// Matricula: 202210342

#include <stdio.h>
#include <stdlib.h>

#define TAM 100 // Tamanho das palavras

int analisadorLexico(char *palavra_teste) { // Analisador lexico para binario
    while(*palavra_teste) {
        if(*palavra_teste != '0' && *palavra_teste != '1') {
            return 0;
        }
        palavra_teste++;
    }
    return 1;
}

int main(void) {
    char palavra_teste[TAM];

    printf("Digite as palavras:\n");

    while (scanf("%s", palavra_teste) == 1) {
        if (analisadorLexico(palavra_teste)) {
            printf("%s reconhecida\n", palavra_teste);
        } else {
            printf("%s rejeitada\n", palavra_teste);
        }
    }
    return 0;
}