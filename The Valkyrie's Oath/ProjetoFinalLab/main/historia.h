#ifndef HISTORIA_H
#define HISTORIA_H

#define NOME_JOGO "The Valkyrie's Oath"

void historia_titulo(void);
void historia_intro(const char *nome);
void historia_fase(int fase);
void historia_vitoria(const char *nome);
void historia_derrota(const char *nome);

#endif
