CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11 -lncurses
DEPS = board.h game.h
#compile step
%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)
#linking
2048:  board.o game.o 2048.o
	$(CC) -o 2048 2048.o board.o game.o
clean:
	rm -f *.o core* *~ 2048
