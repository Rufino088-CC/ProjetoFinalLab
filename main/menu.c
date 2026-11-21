#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define MAGIC 0x52504731  /* identifica que o arquivo e um save valido */

/* ---------- leitura segura ---------- */

static int ler_inteiro(void){
    char buf[32];
    if (fgets(buf, sizeof(buf), stdin) == NULL) return -1;

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
    printf("\n");
    printf("  ========================================\n");
    printf("  |                                      |\n");
    printf("  |        A V E N T U R A   E M  C      |\n");
    printf("  |         ~ Um RPG no terminal ~       |\n");
    printf("  |                                      |\n");
    printf("  ========================================\n\n");
}

void mostrar_instrucoes(void){
    printf("\n=========== INSTRUCOES ===========\n");
    printf("- Explore as fases com W, A, S, D (depois Enter).\n");
    printf("- B = bau (arma ou pocao), E = inimigo, S = saida.\n");
    printf("- Armas tem raridade: Comum, Incomum e Epica.\n");
    printf("- Voce so pode carregar UMA arma; ao ganhar outra,\n");
    printf("  escolha se quer trocar (S/N).\n");
    printf("- No combate: Z ataca, X defende, C usa pocao.\n");
    printf("- Pressione P no mapa para usar uma pocao.\n");
    printf("- Se sua vida chegar a 0, voce perde.\n");
    printf("- Chegue a saida da ultima fase para vencer.\n");
    printf("- Pressione Q para salvar e sair da partida.\n");
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

/* ---------- criacao / liberacao ---------- */

Personagem *novo_jogo(void){
    Personagem *p = malloc(sizeof(Personagem));
    if (p == NULL) return NULL;

    p->itens = malloc(sizeof(Inventario));
    if (p->itens == NULL){ free(p); return NULL; }

    p->itens->arma = malloc(sizeof(Armas));
    p->itens->pocoes = malloc(sizeof(Pocao));
    if (p->itens->arma == NULL || p->itens->pocoes == NULL){
        liberar_personagem(p);
        return NULL;
    }

    printf("\nDigite o nome do seu personagem: ");
    ler_texto(p->nome, sizeof(p->nome));
    if (strlen(p->nome) == 0) strcpy(p->nome, "Heroi");
    printf("Seu nome ficou: %s (maximo de %d letras)\n",
           p->nome, (int)sizeof(p->nome) - 1);

    /* status iniciais */
    p->vida = VIDA_MAX;
    p->itens->ouro = 0;

    strcpy(p->itens->arma->nome, "Espada Velha");
    strcpy(p->itens->arma->raridade, "Comum");
    p->itens->arma->dano = 2;

    p->itens->pocoes->cura = 3;
    p->itens->pocoes->quantidade = 1;

    printf("\nBem-vindo, %s! Sua aventura comeca agora...\n\n", p->nome);
    return p;
}

void liberar_personagem(Personagem *p){
    if (p == NULL) return;
    if (p->itens != NULL){
        free(p->itens->arma);
        free(p->itens->pocoes);
        free(p->itens);
    }
    free(p);
}

/* ---------- salvar / carregar ---------- */
/* Nao da pra gravar os ponteiros direto (o endereco muda a cada execucao),
   entao gravamos o CONTEUDO apontado, campo por campo. */

int salvar_jogo(const Personagem *p, const char *arquivo){
    FILE *f = fopen(arquivo, "wb");
    if (f == NULL){
        printf("Erro ao criar o arquivo de save!\n");
        return 0;
    }

    int magic = MAGIC;
    fwrite(&magic, sizeof(int), 1, f);
    fwrite(p->nome, sizeof(p->nome), 1, f);
    fwrite(&p->vida, sizeof(float), 1, f);
    fwrite(&p->itens->ouro, sizeof(int), 1, f);
    fwrite(p->itens->arma, sizeof(Armas), 1, f);
    fwrite(p->itens->pocoes, sizeof(Pocao), 1, f);

    fclose(f);
    printf("Jogo salvo com sucesso!\n");
    return 1;
}

Personagem *carregar_jogo(const char *arquivo){
    FILE *f = fopen(arquivo, "rb");
    if (f == NULL) return NULL;   /* nao existe save */

    int magic = 0;
    if (fread(&magic, sizeof(int), 1, f) != 1 || magic != MAGIC){
        printf("Arquivo de save invalido ou corrompido!\n");
        fclose(f);
        return NULL;
    }

    Personagem *p = malloc(sizeof(Personagem));
    if (p == NULL){ fclose(f); return NULL; }
    p->itens = malloc(sizeof(Inventario));
    if (p->itens == NULL){ free(p); fclose(f); return NULL; }
    p->itens->arma = malloc(sizeof(Armas));
    p->itens->pocoes = malloc(sizeof(Pocao));
    if (p->itens->arma == NULL || p->itens->pocoes == NULL){
        liberar_personagem(p);
        fclose(f);
        return NULL;
    }

    int ok = 1;
    ok &= fread(p->nome, sizeof(p->nome), 1, f) == 1;
    ok &= fread(&p->vida, sizeof(float), 1, f) == 1;
    ok &= fread(&p->itens->ouro, sizeof(int), 1, f) == 1;
    ok &= fread(p->itens->arma, sizeof(Armas), 1, f) == 1;
    ok &= fread(p->itens->pocoes, sizeof(Pocao), 1, f) == 1;
    fclose(f);

    if (!ok){
        printf("Save incompleto!\n");
        liberar_personagem(p);
        return NULL;
    }
    return p;
}

Personagem *continuar_jogo(void){
    Personagem *p = carregar_jogo(ARQUIVO_SAVE);
    if (p == NULL){
        printf("\nNenhum jogo salvo encontrado. Comece um Novo jogo!\n");
        return NULL;
    }
    printf("\nJogo carregado! Bem-vindo de volta, %s.\n\n", p->nome);
    return p;
}