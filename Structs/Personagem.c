#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inventario.c>

typedef struct{
    float vida;
    float vida_max;
    char nome[7];
    Inventario *itens;
}Personagem;

