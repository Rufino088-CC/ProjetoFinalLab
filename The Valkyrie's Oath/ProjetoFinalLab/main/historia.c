#include <stdio.h>
#include "historia.h"
#include "util.h"

void historia_titulo(void){
    printf("\n");
    printf("  ==============================================\n");
    printf("  |                                            |\n");
    printf("  |        T H E   V A L K Y R I E ' S         |\n");
    printf("  |                O  A  T  H                  |\n");
    printf("  |                                            |\n");
    printf("  |        ~ Um juramento. Tres reinos. ~      |\n");
    printf("  |                                            |\n");
    printf("  ==============================================\n\n");
}

void historia_intro(const char *nome){
    limpar_tela();
    printf("\n  ----------------- PROLOGO -----------------\n\n");
    printf("  Os portoes de Valhalla estao selados.\n");
    printf("  Odin silenciou, e os herois caidos nao encontram descanso.\n\n");
    printf("  Voce, %s, valquiria de juramento antigo,\n", nome);
    printf("  jurou trazer de volta a chama do Salao dos Mortos.\n\n");
    printf("  Para isso, precisara atravessar tres reinos\n");
    printf("  e vencer o que guarda cada um deles.\n");
    printf("  O juramento esta feito. Nao ha volta.\n");
    pausar();
}

void historia_fase(int fase){
    limpar_tela();
    printf("\n  ==================================\n");
    switch (fase){
        case 0:
            printf("   REINO 1: AS CATACUMBAS DE NIFLHEIM\n");
            printf("  ==================================\n");
            printf("  O ar e frio e os corredores cheiram a cinzas.\n");
            printf("  Algo se move entre as paredes de pedra...\n");
            break;
        case 1:
            printf("   REINO 2: A FLORESTA DE JOTUNHEIM\n");
            printf("  ==================================\n");
            printf("  Arvores gigantes escondem trilhas estreitas.\n");
            printf("  Os gigantes ja sabem que voce chegou.\n");
            break;
        case 2:
            printf("   REINO 3: O SALAO DE HEL\n");
            printf("  ==================================\n");
            printf("  Aqui termina o caminho dos mortos.\n");
            printf("  Ao fundo, a saida para Valhalla brilha fraca.\n");
            break;
        default:
            printf("   REINO DESCONHECIDO\n");
            printf("  ==================================\n");
            break;
    }
    pausar();
}

void historia_vitoria(const char *nome){
    printf("\n  *************** VITORIA ***************\n\n");
    printf("  %s ergue a lanca e os portoes de Valhalla se abrem.\n", nome);
    printf("  A chama dos herois volta a arder no grande salao.\n");
    printf("  O juramento foi cumprido.\n\n");
    printf("  Fim de %s.\n", NOME_JOGO);
    printf("  ***************************************\n");
}

void historia_derrota(const char *nome){
    printf("\n  ================ DERROTA ================\n\n");
    printf("  %s cai, e o juramento fica incompleto.\n", nome);
    printf("  Mas as valquirias nunca esquecem:\n");
    printf("  quem jurou pode tentar de novo.\n");
    printf("  =========================================\n");
}
