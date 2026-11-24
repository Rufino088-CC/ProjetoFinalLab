#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Personagem.h"
#include "jogo.h"
#include "loja.h"
#include "util.h"

#define ARMAS_LOJA 3
#define PRECO_POCAO 10

// Armas: sorteadas uma vez por fase e ficam "vendidas" depois de compradas
static Armas estoque[NUM_FASES][ARMAS_LOJA];
static int vendido[NUM_FASES][ARMAS_LOJA];
static int gerado[NUM_FASES] = {0};

void loja_resetar(void) {
    memset(estoque, 0, sizeof(estoque));
    memset(vendido, 0, sizeof(vendido));
    memset(gerado, 0, sizeof(gerado));
}

int loja_salvar(FILE *f) {
    int ok = 1;
    ok &= fwrite(estoque, sizeof(estoque), 1, f) == 1;
    ok &= fwrite(vendido, sizeof(vendido), 1, f) == 1;
    ok &= fwrite(gerado, sizeof(gerado), 1, f) == 1;
    return ok;
}

int loja_carregar(FILE *f) {
    Armas e[NUM_FASES][ARMAS_LOJA];
    int v[NUM_FASES][ARMAS_LOJA];
    int g[NUM_FASES];

    int ok = 1;
    ok &= fread(e, sizeof(e), 1, f) == 1;
    ok &= fread(v, sizeof(v), 1, f) == 1;
    ok &= fread(g, sizeof(g), 1, f) == 1;
    if (!ok) return 0;

    for (int i = 0; i < NUM_FASES; i++) {
        for (int j = 0; j < ARMAS_LOJA; j++) {
            e[i][j].nome[sizeof(e[i][j].nome) - 1] = '\0';
            e[i][j].raridade[sizeof(e[i][j].raridade) - 1] = '\0';
        }
    }
    memcpy(estoque, e, sizeof(estoque));
    memcpy(vendido, v, sizeof(vendido));
    memcpy(gerado, g, sizeof(gerado));
    return 1;
}

int preco_arma(const Armas *a) {
    return (int)(a->dano * 3);
}

static void gerar_estoque(int f) {
    for (int i = 0; i < ARMAS_LOJA; i++) {
        estoque[f][i] = ganhou_arma();
        vendido[f][i] = 0;
    }
    gerado[f] = 1;
}

// Compra de arma. Escreve o resultado em msg. Retorna 1 se comprou.
static int comprar_arma(Personagem *p, Armas *item, char *msg, size_t tam) {
    int preco = preco_arma(item);
    int credito = 0;     // quanto o jogador recebe pela arma antiga

    if (p->itens->ouro < preco) {
        snprintf(msg, tam, "Ouro insuficiente! %s custa %d e voce tem %d.",
                 item->nome, preco, p->itens->ouro);
        return 0;
    }

    if (p->itens->arma != NULL) {
        credito = preco_arma(p->itens->arma) / 2;
        printf("\nSua arma: %s (dano %.0f, %s)\n",
               p->itens->arma->nome, p->itens->arma->dano, p->itens->arma->raridade);
        printf("Nova arma: %s (dano %.0f, %s)\n", item->nome, item->dano, item->raridade);
        printf("Sua arma antiga sera vendida por %d de ouro.\n", credito);
        if (!perguntar_sn("Comprar e trocar de arma?")) {
            snprintf(msg, tam, "Compra cancelada.");
            return 0;
        }
    } else {
        printf("\n");
        if (!perguntar_sn("Confirmar a compra?")) {
            snprintf(msg, tam, "Compra cancelada.");
            return 0;
        }
    }

    if (p->itens->arma == NULL) {
        p->itens->arma = malloc(sizeof(Armas));
        if (p->itens->arma == NULL) {
            snprintf(msg, tam, "Erro de memoria.");
            return 0;
        }
    }
    *p->itens->arma = *item;
    p->itens->ouro = p->itens->ouro - preco + credito;
    snprintf(msg, tam, "Voce comprou %s por %d de ouro!", item->nome, preco);
    return 1;
}

// Compra de pocao: se ja tem, soma 1 da mesma cura; se nao tem, sorteia uma.
static int comprar_pocao(Personagem *p, char *msg, size_t tam) {
    if (p->itens->ouro < PRECO_POCAO) {
        snprintf(msg, tam, "Ouro insuficiente! A pocao custa %d e voce tem %d.",
                 PRECO_POCAO, p->itens->ouro);
        return 0;
    }

    if (p->itens->pocoes == NULL) {
        Pocao nova = ganhou_pocao();       // cura sorteada pelo seu pocao.c
        nova.quantidade = 1;               // a loja vende uma por vez
        p->itens->pocoes = malloc(sizeof(Pocao));
        if (p->itens->pocoes == NULL) {
            snprintf(msg, tam, "Erro de memoria.");
            return 0;
        }
        *p->itens->pocoes = nova;
        snprintf(msg, tam, "Voce comprou uma pocao (cura %.0f) por %d de ouro!",
                 nova.cura, PRECO_POCAO);
    } else {
        p->itens->pocoes->quantidade++;
        snprintf(msg, tam, "Voce comprou uma pocao por %d de ouro! Agora tem %d.",
                 PRECO_POCAO, p->itens->pocoes->quantidade);
    }

    p->itens->ouro -= PRECO_POCAO;
    return 1;
}

void abrir_loja(Personagem *p, int fase_atual) {
    char msg[150] = "Bem-vindo! Escolha o que quer comprar.";
    int tecla;

    if (!gerado[fase_atual]) gerar_estoque(fase_atual);

    while (1) {
        limpar_tela();
        printf("=== LOJA DO BROK E EITRI ===\n");
        printf("Seu ouro: %d\n", p->itens->ouro);
        if (p->itens->arma != NULL) {
            printf("Sua arma: %s (dano %.0f, %s)\n",
                   p->itens->arma->nome, p->itens->arma->dano, p->itens->arma->raridade);
        } else {
            printf("Voce nao tem arma.\n");
        }
        if (p->itens->pocoes != NULL) {
            printf("Suas pocoes: %d (cura %.0f)\n",
                   p->itens->pocoes->quantidade, p->itens->pocoes->cura);
        } else {
            printf("Voce nao tem pocoes.\n");
        }

        printf("\n--- ARMAS ---\n");
        for (int i = 0; i < ARMAS_LOJA; i++) {
            if (vendido[fase_atual][i]) {
                printf("[%d] (vendido)\n", i + 1);
            } else {
                Armas *a = &estoque[fase_atual][i];
                printf("[%d] %-22s dano %2.0f  %-8s %3d ouro\n",
                       i + 1, a->nome, a->dano, a->raridade, preco_arma(a));
            }
        }

        printf("\n--- POCAO ---\n");
        printf("[%d] Pocao de cura (3 a 7) %*d ouro\n", ARMAS_LOJA + 1, 12, PRECO_POCAO);

        printf("\n[Q] Sair da loja\n");
        printf("\n%s\n", msg);
        printf("\n> ");

        tecla = ler_tecla();
        printf("%c\n", tecla);

        if (tecla == 'q') break;

        if (tecla >= '1' && tecla < '1' + ARMAS_LOJA) {
            int i = tecla - '1';
            if (vendido[fase_atual][i]) {
                snprintf(msg, sizeof(msg), "Essa arma ja foi vendida.");
            } else if (comprar_arma(p, &estoque[fase_atual][i], msg, sizeof(msg))) {
                vendido[fase_atual][i] = 1;
            }
        }
        else if (tecla == '1' + ARMAS_LOJA) {          // tecla 4
            comprar_pocao(p, msg, sizeof(msg));
        }
        else {
            snprintf(msg, sizeof(msg), "Opcao invalida. Use 1 a %d ou Q.",
                     ARMAS_LOJA + 1);
        }
    }
}


