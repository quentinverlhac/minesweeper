minesweeper : main.o GameController.o
	g++ build/main.o build/GameController.o -o minesweeper

main.o : src/main.cc src/GameController.h
	g++ -c src/main.cc -o build/main.o

GameController.o : src/GameController.cc src/GameController.h
	g++ -c src/GameController.cc -o build/GameController.o