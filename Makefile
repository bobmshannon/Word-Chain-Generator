CC=g++
CFLAGS=
OBJ    = .o
RM     = rm -fr

all:
	$(CC) $(CFLAGS) WordChainGenerator.cpp -o WordChainGenerator