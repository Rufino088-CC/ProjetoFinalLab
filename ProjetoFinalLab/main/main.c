#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "jogo.h"

int main(void){
    srand((unsigned)time(NULL));

    EstadoJogo estado;
    int opcao;
    do {
        opcao = menu_principal();
        Personagem *p = NULL;

        switch (opcao){
            case 1: p = novo_jogo(&estado);      break;
            case 2: p = continuar_jogo(&estado); break;
            case 3: mostrar_instrucoes(); break;
            case 0: printf("\nAte a proxima, aventureiro!\n"); break;
        }

        if (p != NULL){
            jogar(p, &estado);
            liberar_personagem(p);
        }
    } while (opcao != 0);

    return 0;
}
