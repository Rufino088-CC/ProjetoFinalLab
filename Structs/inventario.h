#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Armas.h"
#include "Pocao.h"

typedef struct {
    int ouro;
    Armas *arma;
    Pocao *pocoes;
} Inventario;

#endif