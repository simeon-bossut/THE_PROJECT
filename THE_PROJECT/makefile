CC= gcc

main: main.o game.o seed.o solver.o sub_function.o
	$(CC) -o main.out main.o seed.o game.o solver.o	sub_function.o
	make clean

clean:
	rm main.o game.o seed.o solver.o sub_function.o