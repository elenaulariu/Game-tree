build: minimax

minimax: main.o tree.o minimax.o
	gcc main.o tree.o minimax.o -o minimax

main.o: main.c

tree.o: tree.h tree.c

minimax.o: minimax.h minimax.c

run:
	./minimax

memcheck:
	valgrind --leak-check=full ./minimax

make clean:
	rm -f *.o minimax