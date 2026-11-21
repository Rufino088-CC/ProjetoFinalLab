#ifndef MENU_H
#define MENU_H

#include "Structs/Personagem.h"

#define ARQUIVO_SAVE "save.dat"

void mostrar_titulo(void);
void mostrar_instrucoes(void);
int menu_principal(void);

Personagem *novo_jogo(void);
Personagem *continuar_jogo(void);
void liberar_personagem(Personagem *p);

int salvar_jogo(const Personagem *p, const char *arquivo);
Personagem *carregar_jogo(const char *arquivo);

#endif