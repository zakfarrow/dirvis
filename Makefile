CC=gcc
TARGET_DIR=src/
TARGET=$(TARGET_DIR)main.c
OUTPUT_DIR=build/
OUTPUT=$(OUTPUT_DIR)dirvis
FLAGS=-Wall -Wextra -ggdb
MODULES=$(TARGET_DIR)dir_print.c $(TARGET_DIR)flags.c $(TARGET_DIR)config.c

$(OUTPUT):
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(TARGET) $(MODULES) $(FLAGS) -o $(OUTPUT)

clean:
	rm -rf $(OUTPUT_DIR)

run:
	./$(OUTPUT)
