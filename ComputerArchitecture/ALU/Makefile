# Makefile

# Default target when just running `make` without any specific target
all: build

# Target for building the project using CMake
build:
	mkdir -p cmake-build-debug
	cd cmake-build-debug && cmake ..
	cmake --build cmake-build-debug --target ALU

# Target for running the executable
run:
	./cmake-build-debug/ALU

# Target for cleaning the build directory
clean:
	rm -rf cmake-build-debug

.PHONY: all build run clean
