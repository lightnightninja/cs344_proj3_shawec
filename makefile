CC = icc
CXX = icpc
CFLAGS = -std=c99 -g

TARGET = shell

SOURCE = shell.o csystem.o

INCLUDES =

default: compile necho reverse

compile: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS}

shell: shell.o
    ${CC} ${CFLAGS} -c shell.c -o shell.o
csystem: csystem.o
    ${CC} ${CFLAGS} -c csystem.c csystem.h -o csystem.o

necho: necho.c
	${CC} ${CFLAGS} necho.c -o necho
reverse: reverse.c
	${CC} ${CFLAGS} reverse.c -o reverse
