#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Armas.h"
#include "Pocao.h"

// arma e pocoes sao ponteiros: NULL significa "nao tem".
typedef struct {
    int ouro;
    Armas *arma;
    Pocao *pocoes;
} Inventario;

// Cria o inventario inicial (0 ouro, Espada Velha e 1 pocao). NULL se faltar memoria.
Inventario *criar_inventario(void);
void liberar_inventario(Inventario *inv);

// Sorteia o que o bau da: 1 = arma, 2 = pocao, 3 = ouro.
int sorteio(void);

// Aplica o premio do bau (tipo vindo de sorteio()) no inventario.
void atualizar_inventario(Inventario *inventario, int tipo);

#endif
