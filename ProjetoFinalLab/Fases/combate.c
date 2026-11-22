#include <stdio.h>
#include <stdlib.h>
#include "Personagem.h"
#include "combate.h"
#include "util.h"

int combate(Personagem *p, int fase_atual){
    float vida_inimigo = 10 + fase_atual * 5;
    int defendendo;
    int tecla;

    printf("\n Um inimigo apareceu!\n");

    while (vida_inimigo > 0 && p->vida > 0){
        // recalcula a cada turno, pois a quantidade muda quando usa pocao
        int qtd_pocoes = (p->itens->pocoes != NULL) ? p->itens->pocoes->quantidade : 0;

        printf("\n--- COMBATE ---\n");
        printf("HP: %.0f/%d | HP inimigo: %.0f | Pocoes: %d\n",
               p->vida, VIDA_MAX, vida_inimigo, qtd_pocoes);

        printf("[Z] Atacar  [X] Defender  [C] Pocao\n> ");
        tecla = ler_tecla();
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
        } else if (tecla == 'c') {
            if (qtd_pocoes > 0) {
                float falta = VIDA_MAX - p->vida;
                if (falta <= 0){
                    printf("Sua vida ja esta cheia!\n");
                    continue;                              // nao gasta o turno
                } else {
                    float cura = p->itens->pocoes->cura;
                    if (cura > falta) cura = falta;
                    p->vida += cura;
                    printf("Voce usou uma pocao! +%.0f de vida.\n", cura);

                    p->itens->pocoes->quantidade--;
                    if (p->itens->pocoes->quantidade <= 0){
                        free(p->itens->pocoes);
                        p->itens->pocoes = NULL;
                    }
                }
            } else {
                printf("Voce nao tem pocoes! Perdeu o turno.\n");
            }
        } else {
            printf("Tecla invalida! Use Z, X ou C.\n");
            continue;                                      // tecla errada nao gasta o turno
        }

        // Turno do inimigo (so se ainda estiver vivo)
        if (vida_inimigo > 0) {
            float dano = 2 + fase_atual + rand() % 4;
            if (defendendo) dano = dano / 2;
            p->vida -= dano;
            if (p->vida < 0) p->vida = 0;
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
