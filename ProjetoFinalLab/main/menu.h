#ifndef MENU_H
#define MENU_H

#include "Personagem.h"
#include "jogo.h"

#define ARQUIVO_SAVE "save.dat"

void mostrar_titulo(void);
void mostrar_instrucoes(void);
int menu_principal(void);

// Preenchem tambem o EstadoJogo (fase, posicao e mapa).
Personagem *novo_jogo(EstadoJogo *e);
Personagem *continuar_jogo(EstadoJogo *e);

// Grava/le: nome, vida, ouro, arma, pocoes, fase, posicao, mapa e estoque da loja.
int salvar_jogo(const Personagem *p, const EstadoJogo *e, const char *arquivo);
Personagem *carregar_jogo(EstadoJogo *e, const char *arquivo);

#endif
