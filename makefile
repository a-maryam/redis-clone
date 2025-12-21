# defining C compiler, flags, directory names
CC = gcc
CFLAGS = -Wall -Wextra -g
all: 
	$(CC) $(CFLAGS) main.c -o redis
	