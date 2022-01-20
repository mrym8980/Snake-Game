all: compile run

compile:
	cls
	g++ src/menu.cpp src/core.cpp main.cpp -I "D:\SFML-2.5.1\include" -o bin\snake-game -L"D:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
run:
	./bin/snake-game.exe
