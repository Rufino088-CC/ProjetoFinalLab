#ifndef COMBATE_H
#define COMBATE_H

#include "Personagem.h"

// Combate por turnos (Atacar / Defender / Pocao).
// fase_atual comeca em 0. Retorna 1 se o jogador venceu, 0 se morreu.
int combate(Personagem *p, int fase_atual);

#endif
