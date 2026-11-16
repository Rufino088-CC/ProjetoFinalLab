#ifndef COMBATE_H
#define COMBATE_H

#include "personagem.h"

// Combate por turnos (Atacar / Defender / Pocao).
// Retorna 1 se o jogador venceu, 0 se morreu.
int combate(Personagem *p, int fase_atual);

#endif
