# defining C compiler, flags, directory names
CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR := src
OBJDIR := obj
INCDIR := include
BINDIR := bin
TESTDIR := tests

all: 
	${CC} ${CFLAGS} ${SRCDIR}/main.c ${SRCDIR}/hash_table.c -o ${BINDIR}/redis

clean:
	rm -rf ${BINDIR}/*
	