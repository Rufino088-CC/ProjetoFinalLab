#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char raridade[20];
    char nome[50];
    float dano;
} Armas;

Armas ganhou_arma(){
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
        "Maca de Pedra", "Espada de Metal", "Marreta de Ouro", "Foice de Ferro", "Machado de Metal", "Adaga Metalica", "Bastao de Ferro","Luvas de aco"
        };

        int sorteio_nome = rand() % 8;
        strcpy(arma.nome, nome_comum[sorteio_nome]);

        arma.dano = (rand() % 5) + 2;

    }

    //Se raridade for incomum, vai sortear uma arma e declarar seu dano de 7-9
    else if (strcmp(arma.raridade, "Incomum") == 0){
        char nome_incomum [8][30] = {
        "Maca em chamas", "Espada Congelada", "Marreta Sonica", "Foice Envenenada", "Machado Eletrico", "Adaga Dupla", "Bastao Magico","Luvas de Aco Cortante"
        };

        int sorteio_nome = rand() % 8;
        strcpy(arma.nome, nome_incomum[sorteio_nome]);

        arma.dano = (rand() % 3) + 7;

    }

    //Se raridade for incomum, vai sortear uma arma e declarar seu dano de 10-12
    else{
        char nome_epico [6][30] = {
        "Trident de Posseidom", "Espada de Guerra", "Foice de Cronos e Perceu", "Foice de Hades", "Machado De Thor", "Clava de Hercules"
        };

        int sorteio_nome = rand() % 6;
        strcpy(arma.nome, nome_epico[sorteio_nome]);

        arma.dano = (rand() % 3) + 10;

    }

    return arma;
}


Armas trocar_arma(Armas arma_em_uso, Armas arma_ganha){
    printf("Sua arma em uso e: %s\nDano de: %.2f\nEla e uma arma %s", arma_em_uso.nome, arma_em_uso.dano, arma_em_uso.raridade);
    printf("Voce acabou de ganhar: %s\nDano de: %.2f\nEla e uma arma %s.", arma_ganha.nome, arma_ganha.dano, arma_ganha.raridade);

    //Laço de repeticao para saber se a pessoa quer trocar de arma
    char resposta = 'a';
    while(toupper(resposta) != 'S' && toupper(resposta) != 'N'){

        printf("Voce deseja trocar de arma?\n");
        scanf(" %c", &resposta);

        if(toupper(resposta) == 'S'){
            arma_em_uso = arma_ganha;
            return arma_em_uso;
        }
        else if(toupper(resposta) == 'N'){
            printf("A arma que voce ganhou foi descartada, pois nao pode ser guardada! ");
            return arma_em_uso;
        }
        else{
            printf("Responda com S ou N! ");
        }
    }

    return arma_em_uso;
}