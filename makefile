minesweeper : main.o GameController.o Grid.o
	g++ -std=c++17 build/main.o build/GameController.o build/Grid.o -o minesweeper

main.o : src/main.cc src/GameController.h
	g++ -std=c++17 -c src/main.cc -o build/main.o 

GameController.o : src/GameController.cc src/GameController.h
	g++ -std=c++17 -c src/GameController.cc -o build/GameController.o

Grid.o: src/Grid.cc src/Grid.h
	g++ -std=c++17 -c src/Grid.cc -o build/Grid.o