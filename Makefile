TARGET=main
OBJECTS=util.o axpy.o

CPPFLAGS=-O2 -Wall -fopenmp
LDLIBS=-lm -lpthread

all: $(TARGET)

$(TARGET): $(OBJECTS)

clean:
	rm -rf $(TARGET) $(OBJECTS)