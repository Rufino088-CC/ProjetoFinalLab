#!/bin/bash
x86_64-w64-mingw32-gcc -Wall -Wextra -std=c11 -IStructs -IFases -Imain main/*.c Structs/*.c Fases/*.c -o jogo.exe && echo "jogo.exe gerado"
