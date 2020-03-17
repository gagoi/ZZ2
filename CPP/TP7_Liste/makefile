SRC=$(wildcard *.cpp)  
EXE=out

CXXFLAGS+=-Wall -Wextra -MMD -g -O2 -std=c++11 -Wcatch-value=0
LDFLAGS= 

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
