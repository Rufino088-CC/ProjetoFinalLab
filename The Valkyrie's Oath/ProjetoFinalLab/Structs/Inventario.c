#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

Inventario *criar_inventario(void){
    Inventario *inv = malloc(sizeof(Inventario));
    if (inv == NULL) return NULL;

    inv->arma = malloc(sizeof(Armas));
    inv->pocoes = malloc(sizeof(Pocao));
    if (inv->arma == NULL || inv->pocoes == NULL){
        liberar_inventario(inv);
        return NULL;
    }

    inv->ouro = 0;

    strcpy(inv->arma->nome, "Espada Velha");
    strcpy(inv->arma->raridade, "Comum");
    inv->arma->dano = 2;

    inv->pocoes->cura = 3;
    inv->pocoes->quantidade = 1;

    return inv;
}

void liberar_inventario(Inventario *inv){
    if (inv == NULL) return;
    free(inv->arma);
    free(inv->pocoes);
    free(inv);
}

int sorteio(void){
    int tabela[8] = {
        1, 1, 2, 2, 2, 3, 3, 3
    };

    return tabela[rand() % 8];
}

void atualizar_inventario(Inventario *inventario, int tipo){

    // Caso o personagem tenha ganhado uma arma
    if (tipo == 1){
        Armas arma_ganha = ganhou_arma();

        if (inventario->arma == NULL){
            inventario->arma = malloc(sizeof(Armas));
            if (inventario->arma == NULL) return;
            *inventario->arma = arma_ganha;
            printf("\nVoce encontrou uma arma: %s (dano %.0f, %s)!\n",
                   arma_ganha.nome, arma_ganha.dano, arma_ganha.raridade);
        } else {
            *inventario->arma = trocar_arma(*inventario->arma, arma_ganha);
        }
    }

    // Caso o personagem tenha ganhado uma pocao
    else if (tipo == 2){
        Pocao pocao_ganha = ganhou_pocao();

        if (inventario->pocoes == NULL){
            inventario->pocoes = malloc(sizeof(Pocao));
            if (inventario->pocoes == NULL) return;
            *inventario->pocoes = pocao_ganha;
            printf("\nVoce encontrou %d pocao(oes) de cura %.0f!\n",
                   pocao_ganha.quantidade, pocao_ganha.cura);
        } else {
            *inventario->pocoes = somar_pocao(inventario->pocoes, &pocao_ganha);
            printf("\nSuas pocoes agora: %d (cura %.0f)\n",
                   inventario->pocoes->quantidade, inventario->pocoes->cura);
        }
    }

    // Caso o personagem tenha ganhado ouro
    else if (tipo == 3){
        int ouro_ganho = (rand() % 16) + 5;

        inventario->ouro += ouro_ganho;

        printf("\nVoce encontrou %i moedas de ouro!\n", ouro_ganho);
        printf("Ouro atual: %i\n", inventario->ouro);
    }
}
