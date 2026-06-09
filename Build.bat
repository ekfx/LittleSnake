@ECHO OFF

ECHO -----------COMPILADOR PORTATIL-----------
ECHO Compilando Arquivo Executavel Portavel...
ECHO.

g++ src/*.cpp src/glad.c -Iinclude -Llib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++ -static -o build/Portable.exe

ECHO.
ECHO -----------------------------------------
ECHO.
IF EXIST "build/Portable.exe" (
	ECHO Compilado Com Sucesso!
	ECHO Nome do Arquivo: 'Portable.exe'
) ELSE (
	ECHO Falha da execucao.
)

ECHO.
ECHO -----------------------------------------

pause