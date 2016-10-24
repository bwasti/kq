CC=clang++
CFLAGS=-c -Wall --std=c++14
LDFLAGS=
SOURCES=game_server.cpp #$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game_engine

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	    $(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	    $(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) *.o
