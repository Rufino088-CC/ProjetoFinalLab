#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char raridade;
    char tipo;
} Armas;


typedef struct{
    int aura;
    Armas *arma;
    int pocoes;
} Inventario;


typedef struct{
    float vida;
    char nome[7];
    Inventario *itens;
} Personagem;



int main(){

    return 0;
}