#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Armas.h"
#include "util.h"

Armas ganhou_arma(void){
    Armas arma;
    //lista de raridades da arma e sorteando sua raridade logo em seguida
    char raridades [10][10] = {
        "Comum", "Comum", "Comum", "Comum", "Comum", "Comum", "Comum", "Incomum", "Incomum", "Epica"
    };

    int sorteio_raridade = rand() % 10;
    strcpy(arma.raridade, raridades[sorteio_raridade]);

    //Se raridade for comum, vai sortear o nome de uma arma comum, e declarar seu dano de 2-6
    if (strcmp(arma.raridade, "Comum") == 0){
        char nome_comum [8][20] = {
            "Ulfberht", "Seax", "Sax", "Skeggox", "Spjot", "Atgeir", "Hoggspjot", "Langsax"
        };

        int sorteio_nome = rand() % 8;
        strcpy(arma.nome, nome_comum[sorteio_nome]);

        arma.dano = (rand() % 5) + 2;
    }

    //Se raridade for incomum, vai sortear uma arma e declarar seu dano de 7-9
    else if (strcmp(arma.raridade, "Incomum") == 0){
        char nome_incomum [8][30] = {
            "Tyrfing", "Skofnung", "Dainsleif", "Gram", "Mistilteinn", "Hrunting", "Hofund", "Aettartangi"
        };

        int sorteio_nome = rand() % 8;
        strcpy(arma.nome, nome_incomum[sorteio_nome]);

        arma.dano = (rand() % 3) + 7;
    }

    //Se raridade for epica, vai sortear uma arma e declarar seu dano de 10-12
    else{
        char nome_epico [6][30] = {
            "Mjolnir", "Gungnir", "Gleipnir", "Laevateinn", "Sumarbrander", "Hofud de Heimdall"
        };

        int sorteio_nome = rand() % 6;
        strcpy(arma.nome, nome_epico[sorteio_nome]);

        arma.dano = (rand() % 3) + 10;
    }

    return arma;
}


Armas trocar_arma(Armas arma_em_uso, Armas arma_ganha){
    printf("\nSua arma em uso e: %s\nDano de: %.0f\nEla e uma arma %s.\n",
           arma_em_uso.nome, arma_em_uso.dano, arma_em_uso.raridade);
    printf("\nVoce acabou de ganhar: %s\nDano de: %.0f\nEla e uma arma %s.\n\n",
           arma_ganha.nome, arma_ganha.dano, arma_ganha.raridade);

    if (perguntar_sn("Voce deseja trocar de arma?")){
        return arma_ganha;
    }

    printf("A arma que voce ganhou foi descartada, pois nao pode ser guardada!\n");
    return arma_em_uso;
}