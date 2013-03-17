#Compiler Settings
CC = gcc

#Source Settings
SOURCE = main.c matrix.c tree.c list.c
CFLAGS = -Wall
CINCS = -I./inc
BIN = bin/hakoiri-musume
MKDIR_P = mkdir -p bin/
RM_RF = rm -rf bin/

hakoiri-musume:
	$(MKDIR_P)
	$(CC) $(CFLAGS) $(CINCS) $(SOURCE) -o $(BIN)

clean:
	$(RM_RF)