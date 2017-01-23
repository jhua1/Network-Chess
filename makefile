all: game server

game: game.o parse.o
	gcc -o game game.o parse.o

server: server.o parse.o
	gcc -o server server.o parse.o

game.o: game.c parse.h
	gcc -c game.c

server.o: server.c parse.h
	gcc -c server.c

parse.o: parse.c parse.h
	gcc -c parse.c

clean: 
	rm *.o
	rm *~
	rm a.out
	rm game
	rm server
