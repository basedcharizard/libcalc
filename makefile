CC=gcc
TARGET=build/libcalc.a
TEST=build/calctest
SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

all: $(TARGET) 

$(TARGET): src/calc.o
	ar -cvq $(TARGET) src/calc.o

test: $(OBJECTS)
	$(CC) -o $(TEST) $(OBJECTS)

$(OBJECTS): $(SOURCES)


clean: 
	rm -rf $(TARGET) $(TEST) $(OBJECTS)
