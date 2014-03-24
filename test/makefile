CC          	=  gcc
CXX         	=  g++
CFLAGS      	+= -g -fPIC -Wno-deprecated -Wall

SRC 			=  $(wildcard ./*.cpp)
OBJ 			=  $(patsubst %.cpp, %.o, $(SRC))
EXE				=  $(patsubst %.cpp, %.test, $(SRC))

INCLUDE			=  -I./../include

LIB				=  -lpthread -lgtest
LIB_DIR			=  -L./../lib


#------------------------------------------------------------------------------

all: $(EXE)

include $(patsubst %.cpp, %.d, $(SRC))


%.test: %.o $(filter-out ./../src/main.o, $(patsubst %.cpp, %.o, $(wildcard ./../src/*.cpp)))
#	@echo $(filter-out %main.o, $(patsubst %.cpp, %.o, $(wildcard ./../src/*.cpp)))
#	@echo $(patsubst %.cpp, %.o, $(wildcard ./../src/*.cpp))
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB_DIR) $(LIB)

clean:
	@echo 'clean the project'
	@rm -f $(patsubst %.cpp,%.d,$(SRC))
	@rm -f $(patsubst %.cpp,%.o,$(SRC))
	@rm -f $(EXE)

.PHONY: clean


-include ../make.rules

