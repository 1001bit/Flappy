FLAGS := -Wall -Wextra -std=c++20 -ggdb

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main

all: 
	g++ $(CXX_FLAGS) -Iinclude -Llib/linux src/**/**/*.cpp src/**/*.cpp src/*.cpp -o bin/linux/$(EXECUTABLE) $(LIBRARIES)
win:
	g++ $(CXX_FLAGS) -Iinclude -Llib/win src/**/**/*.cpp src/**/*.cpp src/*.cpp -o bin/linux/$(EXECUTABLE) $(LIBRARIES)
