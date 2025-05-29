CC=gcc
TARGET=main.c
OUTPUT=main
FLAGS=-Wall -Wextra
LIBS=

$(OUTPUT):
	$(CC) $(TARGET) -o $(OUTPUT)

clean:
	rm $(OUTPUT)

run:
	./$(OUTPUT)
