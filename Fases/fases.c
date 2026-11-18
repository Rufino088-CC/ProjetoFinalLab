#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include "Personagem.c"

#define LARGURA 10
#define ALTURA 10
#define NUM_FASES 3


// Codigos das celulas:
// 0 chao, 1 parede, 2 bau, 3 inimigo, 4 saida
int fases[NUM_FASES][ALTURA][LARGURA] = {
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

int mapa[ALTURA][LARGURA];
int px, py;
int fase = 0;
Personagem heroina = {
    .vida = 50,
    .nome = "Nidhild",
    .itens = NULL
};

void carregar_fase(int f) {
    memcpy(mapa, fases[f], sizeof(mapa));
    px = 0;
    py = 0;
}
 /*.: chao, #: parede, B: bau, E: Inimigo, S: Saida*/ 
void desenhar(void) {
    const char simbolos[] = {'.', '#', 'B', 'E', 'L' ,'S'};

    printf("=== FASE %d/%d ===\n", fase + 1, NUM_FASES);
    printf("Vida: %d/%d | Pocoes: %d | Ouro: %d\n\n", heroina.vida );

    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            if (x == px && y == py) printf("@ ");
            else printf("%c ", simbolos[mapa[y][x]]);
        }
        printf("\n");
    }
    printf("\n@ voce | # parede | B bau | E inimigo | S saida\n");
}
/*OBS: não sei se essa função deve ser aqui que pode usar em outros codigos*/
void pausar(){
    printf("\nPressione qualquer tecla para continuar...")
    getch();
}

int interagir(int celula) {
    if (celula == 2) {
      /*Falta a função do bau de carlim*/
    }else if (celula == 3) {
        if(combate(p, fase)){
            mapa[py][px] = 0;
        }
        pausar(); 
    }else if(celula == 5){

    }else if (celula == 4) {
        if (fase == NUM_FASES - 1) {
            return 1;                          // passou da ultima fase
        }
        fase++;
        carregar_fase(fase);
        printf("Voce avancou para a fase %d!", fase + 1);
    }
    return 0;
}


