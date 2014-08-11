CXX = g++
CXXFLAGS = -Wall -Wextra -O3

SOURCELIST_I = a.cc interpreter.cc
SOURCE_I = $(addprefix src/, $(SOURCELIST_I))
OBJ_I = $(SOURCE_I:%.cc=%.o)

SOURCELIST_C = compiler.cc
SOURCE_C = $(addprefix src/, $(SOURCELIST_C))
OBJ_C = $(SOURCE_C:%.cc=%.o)

all: clean interpreter compiler clean_obj

.cc.o :
	$(CXX) $(CXXFLAGS) -c $< -o $@

interpreter: $(OBJ_I)
	$(CXX) $(CXXFLAGS) -o $@ $^

compiler: $(OBJ_C)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: interpreter compiler clean clean_obj

clean_obj:
	rm -f $(OBJ_I) $(OBJ_C)

clean:
	rm -f interpreter compiler