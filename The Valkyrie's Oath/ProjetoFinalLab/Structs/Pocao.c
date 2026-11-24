#include <stdio.h>
#include <stdlib.h>
#include "Pocao.h"
#include "util.h"

//Chamada logo apos abrir um bau (ou comprar na loja) para sortear uma pocao
Pocao ganhou_pocao(void){
    Pocao pocao;

    pocao.cura = (rand() % 5) + 3;
    pocao.quantidade = (rand() % 3) + 1;

    return pocao;
}


Pocao somar_pocao(Pocao *pocao_equipada, Pocao *pocao_ganha){
    //Se a pocao equipada for igual a que foi ganha, ele ira somar a quantidade
    if (pocao_equipada->cura == pocao_ganha->cura){
        pocao_equipada->quantidade += pocao_ganha->quantidade;
        return *pocao_equipada;
    }

    // Caso seja diferente, ele ira perguntar se quer trocar a pocao equipada
    printf("\nPocao que voce tem  -> Cura: %.0f | Quantidade: %i\n",
           pocao_equipada->cura, pocao_equipada->quantidade);
    printf("Pocao que voce ganhou -> Cura: %.0f | Quantidade: %i\n",
           pocao_ganha->cura, pocao_ganha->quantidade);

    if (perguntar_sn("As pocoes tem cura diferente, voce quer trocar?")){
        return *pocao_ganha;
    }
    return *pocao_equipada;
}
