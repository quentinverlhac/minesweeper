minesweeper : main.o GameController.o
	g++ -std=c++17 build/main.o build/GameController.o -o minesweeper

main.o : src/main.cc src/GameController.h
	g++ -std=c++17 -c src/main.cc -o build/main.o 

GameController.o : src/GameController.cc src/GameController.h
	g++ -std=c++17 -c src/GameController.cc -o build/GameController.o