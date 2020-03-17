#SRC=$(wildcard *.cpp)  
SRC=producteur.cpp statisticien.cpp producteurAleatoire.cpp producteurPremiersEntiers.cpp tests_catch.cpp main.cpp
EXE=cpp3

CXXFLAGS+=-Wall -Wextra -MMD -g -O2
LDFLAGS= #-lSDL

OBJ=$(addprefix build/,$(SRC:.cpp=.o))
DEP=$(addprefix build/,$(SRC:.cpp=.d))

all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.gch

-include $(DEP)
