CC=gcc
TARGET_DIR=src/
TARGET=$(TARGET_DIR)main.c
OUTPUT_DIR=build/
OUTPUT=$(OUTPUT_DIR)dirvis
BINARY_NAME=dirvis
FLAGS=-Wall -Wextra -ggdb -std=c99
MODULES=$(TARGET_DIR)dir_print.c $(TARGET_DIR)flags.c $(TARGET_DIR)config.c

# Installation directories
INSTALL_DIR=/usr/local/bin
USER_BIN_DIR=$(HOME)/bin

# Default target
all: $(OUTPUT)

# Build the program
$(OUTPUT): $(TARGET) $(MODULES)
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(TARGET) $(MODULES) $(FLAGS) -o $(OUTPUT)

# Clean build directory
clean:
	rm -rf $(OUTPUT_DIR)

# Install to system directory (requires sudo)
install: $(OUTPUT)
	sudo cp $(OUTPUT) $(INSTALL_DIR)/$(BINARY_NAME)
	@echo "Installed $(BINARY_NAME) to $(INSTALL_DIR)"
	@echo "You can now run '$(BINARY_NAME)' from anywhere!"

# Install to user's local bin directory
install-user: $(OUTPUT)
	mkdir -p $(USER_BIN_DIR)
	cp $(OUTPUT) $(USER_BIN_DIR)/$(BINARY_NAME)
	@echo "Installed $(BINARY_NAME) to $(USER_BIN_DIR)"
	@echo "Make sure $(USER_BIN_DIR) is in your PATH:"
	@echo "  echo 'export PATH=\"\$$HOME/bin:\$$PATH\"' >> ~/.bashrc"
	@echo "  source ~/.bashrc"

# Uninstall from system
uninstall:
	sudo rm -f $(INSTALL_DIR)/$(BINARY_NAME)
	@echo "Uninstalled $(BINARY_NAME) from $(INSTALL_DIR)"

# Uninstall from user directory
uninstall-user:
	rm -f $(USER_BIN_DIR)/$(BINARY_NAME)
	@echo "Uninstalled $(BINARY_NAME) from $(USER_BIN_DIR)"

# Check if the binary is installed and where
check:
	@echo "Checking for $(BINARY_NAME)..."
	@which $(BINARY_NAME) 2>/dev/null && echo "Found: $$(which $(BINARY_NAME))" || echo "$(BINARY_NAME) not found in PATH"

# Development: rebuild and run
dev: clean $(OUTPUT)

# Help target
help:
	@echo "Available targets:"
	@echo "  all           - Build the program (default)"
	@echo "  clean         - Remove build directory"
	@echo "  install       - Install to system directory (requires sudo)"
	@echo "  install-user  - Install to ~/bin (no sudo required)"
	@echo "  uninstall     - Remove from system directory"
	@echo "  uninstall-user- Remove from ~/bin"
	@echo "  check         - Check if program is installed"
	@echo "  dev           - Clean and build (development cycle)"
	@echo "  help          - Show this help"

# Declare phony targets (targets that don't create files)
.PHONY: all clean install install-user uninstall uninstall-user check dev help
