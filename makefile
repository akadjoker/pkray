CC = g++
CFLAGS = -std=c++17 -O3 # -g -fsanitize=address -fsanitize=undefined -fsanitize=leak -std=c++17
LDFLAGS =-lraylib -lm
TARGET = main
POCKETPY_DIR = ../pocketpy


SOURCES = main.cpp


INCLUDES = -I$(POCKETPY_DIR)/include


LIBS = -L$(POCKETPY_DIR)/lib -lpocketpy

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SOURCES) $(LIBS) $(LDFLAGS)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean