CC=g++
CFLAGS=-Wall -Wno-strict-aliasing -O2 -c -ffast-math $(DEBUG)
LFLAGS=-lSDL2 -lm -pthread -lrt
SOURCES=main.cpp
# netListen.cpp

OBJECTS=$(SOURCES:.cpp=.o)

.PHONY: debug remake clean

run: $(OBJECTS)
	$(CC) $(OBJECTS) $(DEBUG) -o run $(LFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

#netListen.o: netListen.cpp
#	$(CC) $(CFLAGS) netListen.cpp

clean:
	rm -f *.o run

debug:
	$(MAKE) DEBUG="-g -O0"
	
remake:
	$(MAKE) clean
	$(MAKE)
