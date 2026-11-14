#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
    float cura;
    int quantidade;
}Pocao;

//Chamada logo apos abrir um bau, se for possivel irei criar um na arma e fazer uma funcao para escolher se a pessoa ganhou arma ou pocao!! 
Pocao ganhou_pocao(){
    Pocao pocao;

    pocao.cura = (rand() % 6) + 1;
    pocao.quantidade = (rand() % 3) + 1;

    return pocao;
}


Pocao somar_pocao(Pocao *pocao_equipada, Pocao *pocao_ganha){
    //Se a poção equipar for igual a q foi ganhou, ele ira somar a quantidade
    if (pocao_equipada->cura == pocao_ganha->cura){
        pocao_equipada->quantidade += pocao_ganha->quantidade;
        return *pocao_equipada;
    }
    
    // Caso seja diferente, ele ira perguntar se quer trocar a pocao equipada
    else{
        char resposta;

        printf("Pocao que voce tem: ");
        printf("Cura: %.2f\nQuantidade: %i", pocao_equipada->cura, pocao_equipada->quantidade);
        printf("Pocao que voce gahou: ");
        printf("Cura: %.2f\nQuantidade: %i", pocao_ganha->cura, pocao_ganha->quantidade);

        // Laço de repeticao caso ele responda algo invalido.
        resposta = 'a';

        while (toupper(resposta) != 'S' && toupper(resposta != 'N')){
            printf("As pocoes tem cura diferente, voce quer trocar(S/N)?\n");
            scanf(" %c", &resposta);

            if(toupper(resposta) == 'S'){
                return *pocao_ganha;
            }else if(toupper(resposta) == 'N'){
                return *pocao_equipada;
            }else{
                printf("Por favor, responda com S ou N!");
            }

        }
        
    }
}