#!/bin/bash
gcc -Wall -Wextra -std=c11 -IStructs -IFases -Imain main/*.c Structs/*.c Fases/*.c -o rpg && ./rpg
