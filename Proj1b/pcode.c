#include <stdio.h>
#include <stdlib.h>

#define amax 2047 // Endereço máximo
#define levmax 3 // Profundidade máxima de aninhamento de blocos
#define cxmax 200 // Tamanho máximo do array de instruções
#define stacksize 500 // Tamanho máximo da pilha
#define printaPilha 15 // Primeiros elementos da pilha a serem printados em forma de tabela

typedef enum { // Operações possíveis
    LIT, OPR, LOD, STO, CAL, INTE, JMP, JPC
} fct;

typedef struct {
    fct f; // Operação
    int l; // Nível de aninhamento
    int a; // Endereço
} instruction;

int p, b, t; // Programa, Base, Registrador do topo da pilha
int s[stacksize]; // Pilha de execução

instruction i;

instruction code[] = {
    // Cole aqui os comandos do exercício que deseja realizar
    {INTE, 0, 3},
    {LIT, 0, 0},
    {LIT, 0, 11},
    {LIT, 0, 1},
    {OPR, 0, 3},
    {OPR, 0, 2},
    {INTE, 0, 1},
    {JPC, 0, 10},
    {INTE, 0, 2},
    {JMP, 0, 4},
    {OPR, 0, 0},
};

void interpret() {
    t = 0; // Registrador do topo da pilha
    b = 0; // Base
    p = 0; // Programa

    printf("start pl/0");
    printf("\nt   b   p     f   l   a");
    printf("\n=== === ===   === === ===");

    do {
        i = code[p++];  // Registrador de instrução
        printf("\n%3d %3d %3d   ", t, b, p);
        switch (i.f) {
            case LIT: // Carregamento
                printf("LIT %3d %3d", i.l, i.a);
                t++;
                s[t] = i.a;
                break;
            case OPR: // Operação
                printf("OPR %3d %3d", i.l, i.a);
                switch (i.a) {
                    case 0: // Retorna sub-rotina
                        t = b;
                        p = s[t + 3];
                        b = s[t + 2];
                        break;
                    case 1: // Negativo
                        s[t] = -s[t];
                        break;
                    case 2: // Adição
                        t--;
                        s[t] += s[t + 1];
                        break;
                    case 3: // Subtração
                        t--;
                        s[t] -= s[t + 1];
                        break;
                    case 4: // Multiplicação
                        t--;
                        s[t] *= s[t + 1];
                        break;
                    case 5: // Divisão
                        t--;
                        s[t] /= s[t + 1];
                        break;
                    case 6: // Resto da divisão
                        s[t] = s[t] % 2;
                        break;
                    case 8: // Igualdade
                        t--;
                        s[t] = (s[t] == s[t + 1]);
                        break;
                    case 9: // Diferença
                        t--;
                        s[t] = (s[t] != s[t + 1]);
                        break;
                    case 10: // Menor que
                        t--;
                        s[t] = (s[t] < s[t + 1]);
                        break;
                    case 11: // Maior ou igual a
                        t--;
                        s[t] = (s[t] >= s[t + 1]);
                        break;
                    case 12: // Maior que
                        t--;
                        s[t] = (s[t] > s[t + 1]);
                        break;
                    case 13: // Menor ou igual a
                        t--;
                        s[t] = (s[t] <= s[t + 1]);
                        break;
                }
                break;
            case LOD: // LOAD
                printf("LOD %3d %3d", i.l, i.a);
                t++;
                s[t] = s[b + i.a];
                break;
            case STO: // STORE
                printf("STO %3d %3d", i.l, i.a);
                s[b + i.a] = s[t];
                t--;
                break;
            case CAL: // CALL
                printf("CAL %3d %3d", i.l, i.a);
                s[t + 1] = b;
                s[t + 2] = p;
                s[t + 3] = b;
                b = t + 1;
                p = i.a;
                break;
            case INTE: // Incrementa T
                printf("INT %3d %3d", i.l, i.a);
                t += i.a;
                break;
            case JMP: // Jump
                printf("JMP %3d %3d", i.l, i.a);
                p = i.a;
                break;
            case JPC: // Jump condicional
                printf("JPC %3d %3d", i.l, i.a);
                if (s[t] == 0) {
                    p = i.a;
                }
                t--;
                break;
        }
        printf("      Pilha: ");
        for(int aux = 0 ; aux < printaPilha ; aux++) {
            printf("%5d", s[aux]);
        }
        printf("\n");
    } while (p != 0);
    printf("end pl/0\n");
}

int main(void) {
    interpret();
    return 0;
}