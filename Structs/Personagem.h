#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Inventario.h"

#define VIDA_MAX 50

typedef struct {
    float vida;
    char nome[8];
    Inventario *itens;
} Personagem;

#endif