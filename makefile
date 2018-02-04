compile:
	g++ -std=c++11 -o runGame *.cpp -lsfml-graphics -lsfml-window -lsfml-system
run:
	./runGame
clean:
	rm *.o runGame