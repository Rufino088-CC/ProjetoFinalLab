#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "util.h"

#ifdef _WIN32
#include <conio.h>

int ler_tecla(void){
    fflush(stdout);
    int c = _getch();
    if (c == 0 || c == 224){      // teclas especiais (setas): descarta o 2o codigo
        _getch();
        return 0;
    }
    return tolower(c);
}

void limpar_tela(void){
    system("cls");
}

#else
#include <termios.h>
#include <unistd.h>

int ler_tecla(void){
    fflush(stdout);
    int c;

    if (!isatty(STDIN_FILENO)){     // entrada redirecionada (testes automaticos)
        do { c = getchar(); } while (c == '\n' || c == '\r');
    } else {
        struct termios antigo, novo;
        tcgetattr(STDIN_FILENO, &antigo);
        novo = antigo;
        novo.c_lflag &= ~(ICANON | ECHO);
        novo.c_cc[VMIN] = 1;
        novo.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &novo);
        c = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &antigo);
    }

    if (c == EOF){                  // entrada fechada: nao ha mais como jogar
        printf("\n");
        exit(0);
    }
    return tolower(c);
}

void limpar_tela(void){
    printf("\033[2J\033[H");
    fflush(stdout);
}
#endif

void pausar(void){
    printf("\nPressione qualquer tecla para continuar...");
    ler_tecla();
    printf("\n");
}

int perguntar_sn(const char *pergunta){
    while (1){
        printf("%s (S/N): ", pergunta);
        int t = ler_tecla();
        if (t == 's'){ printf("S\n"); return 1; }
        if (t == 'n'){ printf("N\n"); return 0; }
        printf("\nResponda com S ou N!\n");
    }
}
