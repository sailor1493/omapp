TARGET=main
OBJECTS=util.o work.o
CC=clang

CPPFLAGS=-O2 -Wall -fopenmp
LDLIBS=-lm -lpthread

all: $(TARGET)

$(TARGET): $(OBJECTS)

clean:
	rm -rf $(TARGET) $(OBJECTS)
