#ifndef JOGO_H
#define JOGO_H

#include "Personagem.h"

#define LARGURA 10
#define ALTURA 10
#define NUM_FASES 3

// Tudo o que e preciso (alem do Personagem) para salvar e retomar a partida.
typedef struct {
    int fase;                    // fase atual (0 = fase 1)
    int px, py;                  // posicao do jogador no mapa
    int mapa[ALTURA][LARGURA];   // mapa atual (baus/inimigos ja pegos ficam como chao)
} EstadoJogo;

// Prepara uma partida nova: fase 1, jogador no inicio, loja zerada.
void iniciar_estado(EstadoJogo *e);

// Loop principal da partida (mapa, movimento, interacoes).
void jogar(Personagem *p, EstadoJogo *e);

#endif
