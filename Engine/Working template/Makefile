.PHONY: all clean

EXEC_NAME = Main
GCC = g++
RAYPATH = C:/Raylib/Raylib/src
RAYPATH_LIB = C:/Raylib/Raylib/src
RAYPATH_INC = C:/Raylib/Raylib/src
project_files = src/main.cpp src/GameObject.cpp

all:
	$(GCC) $(project_files) -o $(EXEC_NAME).exe -L$(RAYPATH_LIB) -I$(RAYPATH_INC) -lraylib -lgdi32 -lopengl32 -lwinmm

clean:
	rm *.exe
