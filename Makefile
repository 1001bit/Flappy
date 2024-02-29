FLAGS := -Wall -Wextra -std=c++20 -ggdb

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main
LIBPATH		:= GGE/lib/SFML
INCLUDE		:= -Iinclude -IGGE/include
SOURCE		:= src/*.cpp src/**/*.cpp GGE/src/*.cpp GGE/src/**/*.cpp

all: 
	g++ $(FLAGS) $(INCLUDE) -L$(LIBPATH)/linux $(SOURCE) -o bin/linux/$(EXECUTABLE) $(LIBRARIES)
win:
	g++ $(FLAGS) $(INCLUDE) -L$(LIBPATH)/win $(SOURCE) -o bin/win/$(EXECUTABLE) $(LIBRARIES)
