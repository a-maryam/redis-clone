# defining C compiler, flags, directory names
CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR := src
OBJDIR := obj
INCDIR := include
BINDIR := bin
TESTDIR := tests
SRVDIR := server
SOURCES := $(wildcard $(SRCDIR)/*.c)
TESTSRCS = $(filter-out ${SRCDIR}/driver.c, $(wildcard $(SRCDIR)/*.c)) ${TESTDIR}/tests.c
SERVSRCS := $(filter-out ${SRCDIR}/driver.c ${SRCDIR}/read.c, $(wildcard $(SRCDIR)/*.c)) ${SRVDIR}/server.c

all: 
	${CC} ${CFLAGS} ${SOURCES} -o ${BINDIR}/redis

test:
	${CC} ${CFLAGS} ${TESTSRCS} -o ${BINDIR}/tests

kvserver:
	${CC} ${CFLAGS} ${SERVSRCS} -o ${BINDIR}/kvserver

clean:
	rm -rf ${BINDIR}/*