#ifndef POCAO_H
#define POCAO_H

typedef struct {
    float cura;
    int quantidade;
} Pocao;

Pocao ganhou_pocao(void);
Pocao somar_pocao(Pocao *pocao_equipada, Pocao *pocao_ganha);

#endif