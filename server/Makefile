CC=gcc
CFLAGS=-Wall -Wno-strict-aliasing -O2 -c -ffast-math $(DEBUG)
LFLAGS=-lSDL2 -lm -pthread -lrt
SOURCES=main.c netListen.c vector.c entity.c mesh.c 

OBJECTS=$(SOURCES:.c=.o)

.PHONY: debug remake clean

run: $(OBJECTS)
	$(CC) $(OBJECTS) $(DEBUG) -o run $(LFLAGS)

main.o: main.c entity.h networking.h mesh.h
	$(CC) $(CFLAGS) main.c

netListen.o: netListen.c networking.h
	$(CC) $(CFLAGS) netListen.c

vector.o: vector.c vector.h matrixFuncs.h
	$(CC) $(CFLAGS) vector.c

entity.o: entity.c entity.h
	$(CC) $(CFLAGS) entity.c

mesh.o: mesh.c mesh.h geo3d.h
	$(CC) $(CFLAGS) mesh.c

clean:
	rm -f *.o run

debug:
	$(MAKE) DEBUG="-g -O0"
	
remake:
	$(MAKE) clean
	$(MAKE)
