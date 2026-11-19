#include<stdio.h>
#include<stdlib.h>
#include "Personagem.c"
#include "combate.h"

int combate(Personagem *p, int fases){
    int vida_inimigo = 10 + fase * 5;
    int defendendo;
    char tecla;

    printf("\n Um inimigo apareceu!\n");
    int qtd_pocoes = (p->itens->pocoes != NULL) ? p->itens->pocoes->quantidade : 0;

    while(vida_inimigo > 0 && p->vida > 0){
        printf("\n--- COMBATE ---\n");
        printf("HP: %d | HP inimigo: %d | Pocoes: %d\n", p->vida, vida_inimigo, p->);

        printf("[Z] Atacar  [x] Defender  [C] Pocao\n> ");
        tecla = tolower(getch());
        printf("%c\n", tecla);

        defendendo = 0;

        if (tecla == 'z') {
            float dano = 2 + rand() % 3;                  // sem arma: 2 a 4
            if (p->itens->arma != NULL) {
                dano = p->itens->arma->dano + rand() % 3; // com arma: dano da arma + 0 a 2
            }
            vida_inimigo -= dano;
            printf("Voce atacou e causou %.0f de dano!\n", dano);
        } else if (tecla == 'x') {
            defendendo = 1;
            printf("Voce se defendeu! O proximo dano sera pela metade.\n");
            // Na main é pra ter um Define VIDA_MAX pra dizer a vida maxima que o personagem vai ter
        } else if (tecla == 'c') {
            if (qtd_pocoes > 0) {
                float falta = p->vida_max - p->vida;
                if (falta <= 0){
                    printf("Sua vida ja esta cheia")
                } else{
                    float cura = p->itens->pocoes->cura;
                    if (cura > falta) cura = falta;
                    p->vida += cura;
                    printf("Voce usou uma pocao! +%.0f de vida. \n");

                    p->itens->pocoes->quantidade--;
                    if(p->itens->pocoes->quantidade <= 0){
                        free(p->itens->pocoes);
                        p->itens->pocoes = NULL;
                    }
                }
            } else {
                printf("Voce nao tem pocoes! Perdeu o turno.\n");
            }
        }
        else {
            printf("Tecla invalida! Perdeu o turno.\n");
        } // Turno do inimigo (so se ainda estiver vivo)
        if (vida_inimigo > 0) {
            float dano = 2 + fase_atual + rand() % 4;
            if (defendendo) dano = dano / 2;
            p->vida -= dano;
            printf("O inimigo atacou e causou %.0f de dano!\n", dano);
        }
    }

    if (p->vida <= 0) return 0;
    printf("\nVoce venceu o combate!\n");
    int ouro_dropado = 5 + fase_atual * 3 + rand() % 6;
    p->itens->ouro += ouro_dropado;
    printf("O inimigo deixou %d de ouro!\n", ouro_dropado);
    return 1;
}
