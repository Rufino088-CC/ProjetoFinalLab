#ifndef UTIL_H
#define UTIL_H

// Le UMA tecla sem precisar apertar Enter (retorna em minuscula).
// Funciona no Windows (conio) e no Linux/Mac (termios).
int ler_tecla(void);

// Limpa a tela do terminal.
void limpar_tela(void);

// "Pressione qualquer tecla para continuar..."
void pausar(void);

// Pergunta e espera S ou N. Retorna 1 para sim, 0 para nao.
int perguntar_sn(const char *pergunta);

#endif
