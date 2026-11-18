#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Armas.c"
#include "Pocao.c"

typedef struct{
    int ouro;
    Armas arma;
    Pocao pocoes;
} Inventario;

Inventario criar_inventario(){
    Inventario inventario_inicial;

    inventario_inicial.ouro = 0;

    strcpy(inventario_inicial.arma.nome, "Espada Inicial");
    inventario_inicial.arma.dano = 2;
    strcpy(inventario_inicial.arma.raridade, "Arma de Inicio");

    inventario_inicial.pocoes.cura = 2;
    inventario_inicial.pocoes.quantidade = 4;

    return inventario_inicial;

} 

int sorteio(){
    int sorteio [8] = {
        1, 1, 2, 2, 2, 3, 3, 3
        };

    int numero_sorteado = rand() % 8;

    return(sorteio[numero_sorteado]);
}

Inventario atualizar_inventario(Inventario *inventario, int tipo){

    // Caso o personagem tenha ganhado uma arma
    if(tipo == 1){
        Armas arma_ganha;

        arma_ganha = ganhou_arma();

        inventario->arma = trocar_arma(inventario->arma, arma_ganha);
    }

    // Caso o personagem tenha ganhado uma pocao
    else if(tipo == 2){
        Pocao pocao_ganha;

        pocao_ganha = ganhou_pocao();

        if(inventario->pocoes.quantidade == 0){
            inventario->pocoes = pocao_ganha;
        }
        else{
            inventario->pocoes = somar_pocao(&inventario->pocoes, &pocao_ganha);
        }
    }

    // Caso o personagem tenha ganhado ouro
    else if(tipo == 3){
        int ouro_ganho = (rand() % 16) + 5;

        inventario->ouro += ouro_ganho;

        printf("\nVoce encontrou %i moedas de ouro!\n", ouro_ganho);
        printf("Ouro atual: %i\n", inventario->ouro);
    }

    return *inventario;
}