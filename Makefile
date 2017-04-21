CXXFLAGS:=-Wall -O2 -std=c++11
LIBS:=-lsfml-graphics -lsfml-window -lsfml-system
CXX:=g++
BIN:=dt
#SRC:=$(wildcard *.cpp)
SRC:=draw.cpp dt.cpp
OBJ:=$(patsubst %.cpp,obj/%.o,$(SRC))
ODIR:=obj

NSRC=net.cpp t.cpp

all: $(BIN) net

$(BIN): $(ODIR) $(OBJ)
	$(CXX) -o "$@" $(OBJ) $(CXXFLAGS) $(LIBS)

net: $(NSRC) enum.hpp net.hpp
	$(CXX) -o "$@" $(NSRC) $(CXXFLAGS) -lboost_system -lpthread

$(OBJ): $(ODIR)/%.o: %.cpp
	$(CXX) "$<" -c -o "$@" $(CXXFLAGS)

clean:
	rm -r $(ODIR) $(BIN)

$(ODIR):
	mkdir -p "$@"
