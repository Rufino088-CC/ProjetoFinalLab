#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"
#include "menu.h"
#include "combate.h"
#include "loja.h"
#include "inventario.h"
#include "util.h"
#include "historia.h"

// Codigos das celulas:
// 0 chao, 1 parede, 2 bau, 3 inimigo, 4 saida, 5 loja
static const int fases[NUM_FASES][ALTURA][LARGURA] = {
    // ---------- FASE 1 ----------
    {
        {0,0,0,0,0,0,0,0,0,0},
        {1,0,1,1,1,0,1,0,1,1},
        {0,0,1,2,1,0,1,0,1,4},
        {1,1,1,3,1,0,1,0,1,0},
        {1,1,1,0,1,0,1,0,1,0},
        {1,0,0,0,1,0,1,0,1,0},
        {1,1,3,1,1,0,1,0,1,0},
        {1,0,0,0,1,0,1,0,1,0},
        {1,1,0,1,1,0,1,0,1,0},
        {1,5,0,0,0,0,1,0,0,0}
    },
    // ---------- FASE 2 ----------
    {
        {0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,0,1},
        {0,2,0,0,3,0,0,0,0,1},
        {0,1,1,1,1,1,1,1,0,1},
        {0,0,0,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,0,1,3,1},
        {0,0,0,3,0,1,3,1,3,1},
        {0,1,1,1,0,1,0,1,3,1},
        {0,1,4,1,0,1,0,1,2,1},
        {0,0,0,1,0,0,0,1,5,1}
    },
    // ---------- FASE 3 ----------
    {
        {0,1,1,1,1,1,1,0,0,2},
        {0,1,1,2,0,0,1,0,1,0},
        {0,1,1,0,1,0,1,0,1,0},
        {0,3,0,0,1,0,1,0,1,0},
        {1,1,1,1,1,0,1,3,1,0},
        {0,0,0,0,3,0,1,0,1,0},
        {0,1,1,1,1,1,1,0,1,0},
        {0,1,0,3,0,1,0,0,1,0},
        {0,1,0,1,0,1,0,1,1,0},
        {0,0,0,1,0,0,0,1,1,4}
    }
};

static void carregar_fase(EstadoJogo *e, int f) {
    memcpy(e->mapa, fases[f], sizeof(e->mapa));
    e->fase = f;
    e->px = 0;
    e->py = 0;
}

void iniciar_estado(EstadoJogo *e) {
    carregar_fase(e, 0);
    loja_resetar();
}

/* .: chao, #: parede, B: bau, E: inimigo, S: saida, L: loja */
static void desenhar(const Personagem *p, const EstadoJogo *e) {
    const char simbolos[] = {'.', '#', 'B', 'E', 'S', 'L'};
    int qtd_pocoes = (p->itens->pocoes != NULL) ? p->itens->pocoes->quantidade : 0;

    printf("=== FASE %d/%d ===\n", e->fase + 1, NUM_FASES);
    printf("%s | Vida: %.0f/%d | Pocoes: %d | Ouro: %d\n",
           p->nome, p->vida, VIDA_MAX, qtd_pocoes, p->itens->ouro);
    if (p->itens->arma != NULL) {
        printf("Arma: %s (dano %.0f, %s)\n",
               p->itens->arma->nome, p->itens->arma->dano, p->itens->arma->raridade);
    } else {
        printf("Arma: nenhuma\n");
    }
    printf("\n");

    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            if (x == e->px && y == e->py) printf("@ ");
            else printf("%c ", simbolos[e->mapa[y][x]]);
        }
        printf("\n");
    }
    printf("\n@ voce | # parede | B bau | E inimigo | S saida | L loja\n");
    printf("[W A S D] mover  [P] usar pocao  [Q] salvar e sair\n> ");
}

// Usa uma pocao fora de combate.
static void usar_pocao_mapa(Personagem *p) {
    if (p->itens->pocoes == NULL) {
        printf("\nVoce nao tem pocoes!\n");
    } else if (p->vida >= VIDA_MAX) {
        printf("\nSua vida ja esta cheia!\n");
    } else {
        float falta = VIDA_MAX - p->vida;
        float cura = p->itens->pocoes->cura;
        if (cura > falta) cura = falta;
        p->vida += cura;
        printf("\nVoce usou uma pocao! +%.0f de vida.\n", cura);

        p->itens->pocoes->quantidade--;
        if (p->itens->pocoes->quantidade <= 0) {
            free(p->itens->pocoes);
            p->itens->pocoes = NULL;
        }
    }
    pausar();
}

// Retorna 0 = segue o jogo, 1 = zerou o jogo, 2 = jogador morreu.
static int interagir(Personagem *p, EstadoJogo *e, int celula) {
    if (celula == 2) {
        int tipo = sorteio();
        atualizar_inventario(p->itens, tipo);
        e->mapa[e->py][e->px] = 0;
        pausar();
    } else if (celula == 3) {
        if (combate(p, e->fase)) {
            e->mapa[e->py][e->px] = 0;
            pausar();
        } else {
            return 2;
        }
    } else if (celula == 5) {
        abrir_loja(p, e->fase);
    } else if (celula == 4) {
        if (e->fase == NUM_FASES - 1) {
            return 1;                          // passou da ultima fase
        }
        carregar_fase(e, e->fase + 1);
        historia_fase(e->fase);                // texto do novo reino
        salvar_jogo(p, e, ARQUIVO_SAVE);       // salva sozinho a cada fase nova
        pausar();
    }
    return 0;
}

void jogar(Personagem *p, EstadoJogo *e) {
    while (1) {
        limpar_tela();
        desenhar(p, e);

        int tecla = ler_tecla();
        int nx = e->px, ny = e->py;

        if (tecla == 'w') ny--;
        else if (tecla == 'a') nx--;
        else if (tecla == 's') ny++;
        else if (tecla == 'd') nx++;
        else if (tecla == 'p') { usar_pocao_mapa(p); continue; }
        else if (tecla == 'q') {
            printf("\n");
            if (salvar_jogo(p, e, ARQUIVO_SAVE)) {
                printf("Ate a proxima, aventureiro!\n");
            }
            pausar();
            return;
        }
        else continue;                          // tecla sem funcao

        // fora do mapa ou parede: nao anda
        if (nx < 0 || nx >= LARGURA || ny < 0 || ny >= ALTURA) continue;
        if (e->mapa[ny][nx] == 1) continue;

        e->px = nx;
        e->py = ny;

        int resultado = interagir(p, e, e->mapa[ny][nx]);

        if (resultado == 1) {
            limpar_tela();
            historia_vitoria(p->nome);
            printf("Ouro final: %d\n", p->itens->ouro);
            remove(ARQUIVO_SAVE);               // jogo terminado: apaga o save
            pausar();
            return;
        }
        if (resultado == 2) {
            historia_derrota(p->nome);
            printf("(Use \"Continuar\" para voltar ao ultimo save.)\n");
            pausar();
            return;
        }
    }
}