#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "loja.h"
#include "historia.h"

#define MAGIC 0x52504731  /* identifica que o arquivo e um save valido */
#define VERSAO_SAVE 2

/* ---------- leitura segura ---------- */

static int ler_inteiro(void){
    char buf[32];
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;   /* entrada fechada: sai */

    char *fim;
    long v = strtol(buf, &fim, 10);
    if (fim == buf) return -1;          /* nao digitou numero */
    return (int)v;
}

static void ler_texto(char *dest, int tamanho){
    if (fgets(dest, tamanho, stdin) == NULL){
        dest[0] = '\0';
        return;
    }
    if (strchr(dest, '\n') == NULL){
        int c;
        while ((c = getchar()) != '\n' && c != EOF);   /* descarta o excedente */
    } else {
        dest[strcspn(dest, "\n")] = '\0';              /* tira o \n */
    }
}

/* ---------- telas ---------- */

void mostrar_titulo(void){
    historia_titulo();
}

void mostrar_instrucoes(void){
    printf("\n=========== INSTRUCOES ===========\n");
    printf("- Explore as fases com W, A, S, D (sem precisar de Enter).\n");
    printf("- B = bau (arma, pocao ou ouro), E = inimigo, S = saida, L = loja.\n");
    printf("- Armas tem raridade: Comum, Incomum e Epica.\n");
    printf("- Voce so pode carregar UMA arma; ao ganhar outra,\n");
    printf("  escolha se quer trocar (S/N).\n");
    printf("- No combate: Z ataca, X defende, C usa pocao.\n");
    printf("- Pressione P no mapa para usar uma pocao.\n");
    printf("- Se sua vida chegar a 0, voce perde.\n");
    printf("- Chegue a saida da ultima fase para vencer.\n");
    printf("- Pressione Q para salvar e sair da partida.\n");
    printf("- O jogo tambem salva sozinho ao passar de fase.\n");
    printf("==================================\n\n");
}

int menu_principal(void){
    int opcao;

    do {
        mostrar_titulo();
        printf("  1 - Novo jogo\n");
        printf("  2 - Continuar\n");
        printf("  3 - Instrucoes\n");
        printf("  0 - Sair\n\n");
        printf("  Escolha: ");

        opcao = ler_inteiro();

        if (opcao < 0 || opcao > 3){
            printf("\n  Opcao invalida! Digite um numero de 0 a 3.\n");
            opcao = -1;
        }
    } while (opcao == -1);

    return opcao;
}

/* ---------- criacao ---------- */

Personagem *novo_jogo(EstadoJogo *e){
    char nome[64];

    printf("\nDigite o nome do seu personagem: ");
    ler_texto(nome, sizeof(nome));
    if (strlen(nome) == 0) strcpy(nome, "Heroi");

    Personagem *p = criar_personagem(nome);
    if (p == NULL) return NULL;

    iniciar_estado(e);

    printf("Seu nome ficou: %s (maximo de %d letras)\n",
           p->nome, (int)sizeof(p->nome) - 1);
    printf("\nBem-vindo, %s! Sua aventura comeca agora...\n\n", p->nome);
    historia_intro(p->nome);
    historia_fase(0);
    return p;
}

/* ---------- salvar / carregar ---------- */
/* Nao da pra gravar os ponteiros direto (o endereco muda a cada execucao),
   entao gravamos o CONTEUDO apontado, campo por campo. Como arma e pocao
   podem ser NULL (nao tem), antes de cada uma gravamos um "tem?" (0 ou 1). */

int salvar_jogo(const Personagem *p, const EstadoJogo *e, const char *arquivo){
    FILE *f = fopen(arquivo, "wb");
    if (f == NULL){
        printf("Erro ao criar o arquivo de save!\n");
        return 0;
    }

    int magic = MAGIC;
    int versao = VERSAO_SAVE;
    int tem_arma = (p->itens->arma != NULL);
    int tem_pocao = (p->itens->pocoes != NULL);

    int ok = 1;
    ok &= fwrite(&magic, sizeof(int), 1, f) == 1;
    ok &= fwrite(&versao, sizeof(int), 1, f) == 1;
    ok &= fwrite(p->nome, sizeof(p->nome), 1, f) == 1;
    ok &= fwrite(&p->vida, sizeof(float), 1, f) == 1;
    ok &= fwrite(&p->itens->ouro, sizeof(int), 1, f) == 1;

    ok &= fwrite(&tem_arma, sizeof(int), 1, f) == 1;
    if (tem_arma)  ok &= fwrite(p->itens->arma, sizeof(Armas), 1, f) == 1;
    ok &= fwrite(&tem_pocao, sizeof(int), 1, f) == 1;
    if (tem_pocao) ok &= fwrite(p->itens->pocoes, sizeof(Pocao), 1, f) == 1;

    ok &= fwrite(&e->fase, sizeof(int), 1, f) == 1;
    ok &= fwrite(&e->px, sizeof(int), 1, f) == 1;
    ok &= fwrite(&e->py, sizeof(int), 1, f) == 1;
    ok &= fwrite(e->mapa, sizeof(e->mapa), 1, f) == 1;
    ok &= loja_salvar(f);

    ok &= (fclose(f) == 0);

    if (!ok){
        printf("Erro ao gravar o save!\n");
        return 0;
    }
    printf("Jogo salvo com sucesso!\n");
    return 1;
}

Personagem *carregar_jogo(EstadoJogo *e, const char *arquivo){
    FILE *f = fopen(arquivo, "rb");
    if (f == NULL) return NULL;   /* nao existe save */

    int magic = 0, versao = 0;
    if (fread(&magic, sizeof(int), 1, f) != 1 || magic != MAGIC ||
        fread(&versao, sizeof(int), 1, f) != 1 || versao != VERSAO_SAVE){
        printf("Arquivo de save invalido ou de outra versao!\n");
        fclose(f);
        return NULL;
    }

    Personagem *p = criar_personagem("Heroi");
    if (p == NULL){ fclose(f); return NULL; }

    EstadoJogo novo;
    int tem_arma = 0, tem_pocao = 0;
    Armas arma;
    Pocao pocao;

    int ok = 1;
    ok &= fread(p->nome, sizeof(p->nome), 1, f) == 1;
    ok &= fread(&p->vida, sizeof(float), 1, f) == 1;
    ok &= fread(&p->itens->ouro, sizeof(int), 1, f) == 1;

    ok &= fread(&tem_arma, sizeof(int), 1, f) == 1;
    if (ok && tem_arma)  ok &= fread(&arma, sizeof(Armas), 1, f) == 1;
    ok &= fread(&tem_pocao, sizeof(int), 1, f) == 1;
    if (ok && tem_pocao) ok &= fread(&pocao, sizeof(Pocao), 1, f) == 1;

    ok &= fread(&novo.fase, sizeof(int), 1, f) == 1;
    ok &= fread(&novo.px, sizeof(int), 1, f) == 1;
    ok &= fread(&novo.py, sizeof(int), 1, f) == 1;
    ok &= fread(novo.mapa, sizeof(novo.mapa), 1, f) == 1;
    if (ok) ok &= loja_carregar(f);
    fclose(f);

    /* confere se os valores lidos fazem sentido */
    if (ok){
        if (novo.fase < 0 || novo.fase >= NUM_FASES) ok = 0;
        if (novo.px < 0 || novo.px >= LARGURA || novo.py < 0 || novo.py >= ALTURA) ok = 0;
        for (int y = 0; ok && y < ALTURA; y++)
            for (int x = 0; x < LARGURA; x++)
                if (novo.mapa[y][x] < 0 || novo.mapa[y][x] > 5) ok = 0;
    }

    if (!ok){
        printf("Save incompleto ou corrompido!\n");
        liberar_personagem(p);
        return NULL;
    }

    p->nome[sizeof(p->nome) - 1] = '\0';
    if (p->vida > VIDA_MAX) p->vida = VIDA_MAX;
    if (p->vida < 1) p->vida = 1;

    if (tem_arma){
        arma.nome[sizeof(arma.nome) - 1] = '\0';
        arma.raridade[sizeof(arma.raridade) - 1] = '\0';
        *p->itens->arma = arma;
    } else {
        free(p->itens->arma);
        p->itens->arma = NULL;
    }

    if (tem_pocao){
        *p->itens->pocoes = pocao;
    } else {
        free(p->itens->pocoes);
        p->itens->pocoes = NULL;
    }

    *e = novo;
    return p;
}

Personagem *continuar_jogo(EstadoJogo *e){
    Personagem *p = carregar_jogo(e, ARQUIVO_SAVE);
    if (p == NULL){
        printf("\nNenhum jogo salvo encontrado. Comece um Novo jogo!\n");
        return NULL;
    }
    printf("\nJogo carregado! Bem-vindo de volta, %s.\n\n", p->nome);
    return p;
}
