PREFIX?=/usr/local
INSTALL_BIN?=${PREFIX}/bin

INSTALL=/usr/bin/install

CFLAGS+=-pedantic -Wall -Wstrict-prototypes -Wmissing-prototypes -ansi
LDFLAGS+=-pedantic -Wall -ansi -lz

TARGET=sqllogger
OBJECTS=sqllogger.o

install: ${OBJECTS}
	${CC} -o sqllogger ${OBJECTS}

.c.o:
	${CC} -c $< -o $@

clean:
	rm -f ${TARGET}
	rm -f ${OBJECTS}
