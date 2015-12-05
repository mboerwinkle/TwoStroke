CC=gcc
CFLAGS=-Wall -Wno-strict-aliasing -O2 -c -ffast-math $(DEBUG)
LFLAGS=-lSDL2 -lm -pthread -lrt
SOURCES=main.c netListen.c view.c interpret.c

OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: debug remake clean

run: $(OBJECTS)
	$(CC) $(OBJECTS) $(DEBUG) -o run $(LFLAGS)

main.o: main.c networking.h view.h
	$(CC) $(CFLAGS) main.c

netListen.o: netListen.c networking.h interpret.h
	$(CC) $(CFLAGS) netListen.c

view.o: view.c view.h
	$(CC) $(CFLAGS) view.c

interpret.o: interpret.c interpret.h
	$(CC) $(CFLAGS) interpret.c

clean:
	rm -f *.o run

debug:
	$(MAKE) DEBUG="-g -O0"
	
remake:
	$(MAKE) clean
	$(MAKE)
