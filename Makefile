all:
	g++ -std=c++11 main.cpp -o game -Wall -Werror -ggdb -funroll-loops -lncurses
clean:
	rm game
