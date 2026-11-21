#ifndef ARMAS_H
#define ARMAS_H

typedef struct {
    char raridade[20];
    char nome[50];
    float dano;
} Armas;

Armas ganhou_arma(void);
Armas trocar_arma(Armas arma_em_uso, Armas arma_ganha);

#endif