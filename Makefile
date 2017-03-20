CXXFLAGS:=-Wall -O2
LIBS:=-lsfml-graphics -lsfml-window -lsfml-system
CXX:=g++
BIN:=dt
#SRC:=$(wildcard *.cpp)
SRC:=draw.cpp dt.cpp
OBJ:=$(patsubst %.cpp,obj/%.o,$(SRC))
ODIR:=obj

all: $(BIN)

$(BIN): $(ODIR) $(OBJ)
	$(CXX) -o "$@" $(OBJ) $(CXXFLAGS) $(LIBS)

$(OBJ): $(ODIR)/%.o: %.cpp
	$(CXX) "$<" -c -o "$@" $(CXXFLAGS)

clean:
	rm -r $(ODIR) $(BIN)

$(ODIR):
	mkdir -p "$@"
