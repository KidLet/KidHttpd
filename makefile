CC          = gcc
CXX         = g++
CFLAGS      += -g -fPIC -Wno-deprecated -Wall

SRC 		=  $(wildcard ./src/*.cpp)
OBJ 		=  $(wildcard ./src/*.o)
INCLUDE		= -I./include
LIB			= 

#------------------------------------------------------------------------------

include $(patsubst %.cpp,%.d,$(SRC))


all: KidHttpd

KidHttpd: $(OBJ)
	$(CXX) $(OBJ) -o KidHttpd  

clean:
	@echo 'clean the project'
	-rm $(patsubst %.cpp,%.d,$(SRC))
	-rm $(patsubst %.cpp,%.o,$(SRC))

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


