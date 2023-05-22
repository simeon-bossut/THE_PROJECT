CC= gcc

main: main.o game.o seed.o solver.o
	$(CC) -o main main.o seed.o game.o solver.o	
	./main
	make clean
	

clean:
	rm main.o game.o seed.o solver.o main