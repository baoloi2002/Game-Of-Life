CXX := g++
CXXFLAGS := -std=c++20 -Ofast -fopenmp   
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
SRC_DIR := Graphic World
SRC := $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))
OBJ := $(SRC:.cpp=.o)
EXECUTABLE := main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ) main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS)

$(OBJ): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) main.o $(EXECUTABLE)
