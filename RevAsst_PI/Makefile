TARGET = my_program
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
LIBS = -lpigpio -lrt
CXXFLAGS = -I$(INCLUDE_DIR)

PIGPIO_INSTALLED := $(shell command -v pigpiod 2> /dev/null)

all: install_libs $(TARGET)

install_libs:
ifndef PIGPIO_INSTALLED
	@echo "Installing pigpio..."
	@sudo apt-get update
	@sudo apt-get install pigpio
	@echo "Starting pigpiod daemon..."
	@sudo pigpiod
else
	@echo "pigpio is already installed."
endif

$(TARGET): $(OBJ)
	g++ -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ -c $(CXXFLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(OBJ_DIR)

.PHONY: all install_libs run clean
