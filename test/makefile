CC          	=  gcc
CXX         	=  g++
CFLAGS      	+= -g -fPIC -Wno-deprecated -Wall

SRC 		=  $(wildcard ./*.cpp)
OBJ 		=  $(patsubst %.cpp, %.o, $(SRC))
EXE		=  $(patsubst %.cpp, %.test, $(SRC))

INCLUDE		=  -I./../include

LIB		=  -lpthread -lgtest
LIB_DIR		=  -L./../lib


#------------------------------------------------------------------------------

all: $(EXE)

include $(patsubst %.cpp,%.d,$(SRC))

%.test: %.o
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB_DIR) $(LIB)  

clean:
	@echo 'clean the project'
	-@rm $(patsubst %.cpp,%.d,$(SRC))
	-@rm $(patsubst %.cpp,%.o,$(SRC))
	-@rm $(EXE)

.PHONY: clean


#-------------------------------------------------------------------------------


%.d: %.cpp
		@echo "update $@ ..."; \
		echo -n $< | sed s/\.cpp/\.o:/ > $@; \
		$(CC) $(INCLUDE) -MM $< | sed '1s/.*.://' >> $@;

%.o: %.cpp
		$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<


%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<


