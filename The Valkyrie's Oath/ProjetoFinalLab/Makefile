# Uso:  make          -> gera jogo.exe (Windows/MinGW) ou jogo (Linux/Mac)
#       make clean
CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -IStructs -IFases -Imain
SRC    = $(wildcard main/*.c) $(wildcard Structs/*.c) $(wildcard Fases/*.c)

ifeq ($(OS),Windows_NT)
TARGET = jogo.exe
else
TARGET = jogo
endif

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f jogo jogo.exe save.dat
