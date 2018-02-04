all: compile run

run: runGame
	./runGame
clean:
	rm runGame
compile:
	g++ -std=c++11 -o runGame *.cpp -lsfml-graphics -lsfml-window -lsfml-system
