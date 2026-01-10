# defining C compiler, flags, directory names
CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR := src
OBJDIR := obj
INCDIR := include
BINDIR := bin
TESTDIR := tests
SOURCES := $(wildcard $(SRCDIR)/*.c)
TESTSRCS = $(filter-out ${SRCDIR}/driver.c, $(wildcard $(SRCDIR)/*.c)) ${TESTDIR}/tests.c

all: 
	${CC} ${CFLAGS} ${SOURCES} -o ${BINDIR}/redis

clean:
	rm -rf ${BINDIR}/*

test:
	${CC} ${CFLAGS} ${TESTSRCS} -o ${BINDIR}/tests
	