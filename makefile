# defining C compiler, flags, directory names
CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR := src 
OBJDIR := obj 
INCDIR := include 
BINDER := bin 
TESTDIR := tests

all: 
	${CC} ${CFLAGS} main.c -o redis
	