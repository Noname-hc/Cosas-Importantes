CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

SRCS = $(wildcard *.cpp)
TARGET = parcial_Vasquez

.PHONY: help main clear clean

help:
	@echo "Makefile targets for parcial_Vasquez"
	@echo "  make main   - compile all .cpp in this folder and produce executable '$(TARGET)'"
	@echo "  make clear  - remove the executable '$(TARGET)'"
	@echo "  make clean  - same as clear"

main: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -I. -o $(TARGET)
	@echo "Built $(TARGET)"

clear:
	@rm -f $(TARGET)
	@echo "Removed $(TARGET)"

clean: clear
