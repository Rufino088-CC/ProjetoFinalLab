#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "inventario.h"

#define VIDA_MAX 50

typedef struct {
    float vida;
    char nome[8];
    Inventario *itens;
} Personagem;

// Cria um personagem novo (vida cheia, inventario inicial). NULL se faltar memoria.
Personagem *criar_personagem(const char *nome);
void liberar_personagem(Personagem *p);

#endif
