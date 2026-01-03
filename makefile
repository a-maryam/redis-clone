# defining C compiler, flags, directory names
CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR := src
OBJDIR := obj
INCDIR := include
BINDIR := bin
TESTDIR := tests

all: 
	${CC} ${CFLAGS} ${SRCDIR}/driver.c ${SRCDIR}/hash_table.c ${SRCDIR}/read.c ${SRCDIR}/parser.c ${SRCDIR}/struct.c ${SRCDIR}/value_functions.c -o ${BINDIR}/redis

clean:
	rm -rf ${BINDIR}/*

test:
	${CC} ${CFLAGS} ${TESTDIR}/tests.c ${SRCDIR}/hash_table.c ${SRCDIR}/read.c ${SRCDIR}/parser.c ${SRCDIR}/struct.c ${SRCDIR}/value_functions.c -o ${BINDIR}/tests
	