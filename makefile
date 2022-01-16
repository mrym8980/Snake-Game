all: compile run

compile:
	del *.exe
	del bin\*.exe
	cls
#src/menu.cpp main.cpp
#game-core.cpp
	g++ game-core.cpp -I "D:\SFML-2.5.1\include" -o bin\snake-game -L"D:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
run:
	./bin/snake-game.exe