#ifndef LOJA_H
#define LOJA_H

#include "Personagem.h"
#include "Armas.h"

// Quanto uma arma custa na loja (baseado no dano)
int preco_arma(const Armas *a);

// Abre a loja da fase atual. O estoque (3 armas sorteadas) fica guardado
// enquanto o jogo estiver aberto, e o que for comprado fica como "vendido".
void abrir_loja(Personagem *p, int fase_atual);

#endif