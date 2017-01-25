CC = gcc
CFLAGS = -ansi -Wall -pedantic -g
INCLUDES = funcoes.c
SRC =  main.c 


all: proj3

proj3: $(INCLUDES) $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o proj3
