# ProjetoFinalLab
Jogo em C, utilizando os aprendizados no Laboratório de Programação.

## Como compilar
- **Windows:** dê dois cliques em `build.bat` (precisa do gcc/MinGW) ou rode `make`. Gera `jogo.exe`.
- **Linux/Mac:** `make` e depois `./jogo`.
- **Sem compilador:** envie o projeto ao GitHub; a aba *Actions* gera o `jogo.exe` (artefato `jogo-windows`).

## Save
O jogo grava em `save.dat` (na pasta onde o jogo é executado): nome, vida, ouro, arma, poções, fase, posição, mapa e lojas.
Salva ao apertar **Q** e automaticamente ao passar de fase.
