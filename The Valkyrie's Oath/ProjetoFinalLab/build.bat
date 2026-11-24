@echo off
REM Compila o jogo no Windows (precisa do gcc/MinGW no PATH).
gcc -Wall -Wextra -std=c11 -IStructs -IFases -Imain main\*.c Structs\*.c Fases\*.c -o jogo.exe
if errorlevel 1 (
    echo.
    echo ERRO na compilacao.
    pause
    exit /b 1
)
echo.
echo Pronto! Execute jogo.exe
pause
