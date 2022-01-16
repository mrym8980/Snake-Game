all: compile run

compile:
	del *.exe
	cls
#src/menu.cpp main.cpp
	g++ game-core.cpp -I "D:\SFML-2.5.1\include" -o snake-game -L"D:\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
run:
	./snake-game.exe