CC          = gcc
CXX         = g++
CFLAGS      += -g -fPIC -Wno-deprecated -Wall

SRC 		=  $(wildcard ./src/*.cpp)
OBJ 		=  $(patsubst %.cpp,%.o,$(SRC))
INCLUDE		= -I./include
LIB			= 
EXE			= KidHttpd

#------------------------------------------------------------------------------

all: $(EXE)

include $(patsubst %.cpp,%.d,$(SRC))

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o KidHttpd  

clean:
	@echo 'clean the project'
	-rm $(patsubst %.cpp,%.d,$(SRC))
	-rm $(patsubst %.cpp,%.o,$(SRC))
	-rm $(EXE)

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


