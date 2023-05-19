CC= gcc

main: main.o game.o seed.o
	$(CC) -o main main.o game.o seed.o
	./main
	make clean

clean:
	rm main.o game.o seed.o main