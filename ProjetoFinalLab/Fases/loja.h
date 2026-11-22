#ifndef LOJA_H
#define LOJA_H

#include <stdio.h>
#include "Personagem.h"
#include "Armas.h"

// Quanto uma arma custa na loja (baseado no dano)
int preco_arma(const Armas *a);

// Abre a loja da fase atual. O estoque (3 armas sorteadas) fica guardado
// enquanto o jogo estiver aberto, e o que for comprado fica como "vendido".
void abrir_loja(Personagem *p, int fase_atual);

// Esquece o estoque de todas as lojas (usar ao comecar um jogo novo).
void loja_resetar(void);

// Gravam/leem o estoque das lojas no arquivo de save. Retornam 1 se deu certo.
int loja_salvar(FILE *f);
int loja_carregar(FILE *f);

#endif
