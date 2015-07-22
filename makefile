CC = icc
CXX = icpc
CFLAGS = -std=c99 -g

TARGET = shell

SOURCE = shell.c csystem.h

default: shell necho reverse 

compile: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS}

debug: ${SOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${SOURCE} -o ${TARGET} ${LDFLAGS} -DDEBUG

necho: necho.c
	${CC} ${CFLAGS} necho.c -o necho
reverse: reverse.c
	${CC} ${CFLAGS} reverse.c -o reverse
