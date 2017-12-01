all:
	g++ -std=c++11 main.cpp -o snek -Wall -Werror -ggdb -funroll-loops -lncurses
