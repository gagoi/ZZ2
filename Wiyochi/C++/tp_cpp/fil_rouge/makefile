SRC=$(wildcard *.cpp)  
#EXE=$(shell pwd | grep -o \"[^/]*\$\")
EXE=fil_rouge.exe

CXXFLAGS+=-Wall -Wextra -MMD -g -std=c++11
LDFLAGS= #-lSDL

OBJ=$(addprefix build/,$(SRC:.cpp=.o))
DEP=$(addprefix build/,$(SRC:.cpp=.d))

all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)
	./$(EXE)

build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.gch

-include $(DEP)