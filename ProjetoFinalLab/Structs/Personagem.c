#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Personagem.h"

Personagem *criar_personagem(const char *nome){
    Personagem *p = malloc(sizeof(Personagem));
    if (p == NULL) return NULL;

    p->itens = criar_inventario();
    if (p->itens == NULL){
        free(p);
        return NULL;
    }

    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    p->vida = VIDA_MAX;

    return p;
}

void liberar_personagem(Personagem *p){
    if (p == NULL) return;
    liberar_inventario(p->itens);
    free(p);
}
