#
# 文件名称：makefile
# 摘要：    编译整个项目的makefile，不包括测试模块
#
# 当前版本：1.0
# 作者:	    KidLet
# 完成日期：2014年2月17日
#

CC          	=  gcc
CXX         	=  g++
CFLAGS      	+= -g -fPIC -Wno-deprecated -Wall

SRC 		=  $(wildcard ./src/*.cpp)
OBJ 		=  $(patsubst %.cpp,%.o,$(SRC))
INCLUDE		=  -I./include
LIB		=  -lpthread -lgtest
LIB_DIR		=  -L./lib

EXE		=  KidHttpd

#------------------------------------------------------------------------------

all: $(EXE)

include $(patsubst %.cpp,%.d,$(SRC))

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o KidHttpd $(INCLUDE) $(LIB_DIR) $(LIB)

clean:
	@echo 'clean the project'
	-@rm $(patsubst %.cpp,%.d,$(SRC))
	-@rm $(patsubst %.cpp,%.o,$(SRC))
	-@rm $(EXE)

.PHONY: clean

test:
	make -C ./test

.PHONY:	test


#-------------------------------------------------------------------------------


%.d: %.cpp
		@echo "update $@ ..."; \
		echo -n $< | sed s/\.cpp/\.o:/ > $@; \
		$(CC) $(INCLUDE) -MM $< | sed '1s/.*.://' >> $@;

%.o: %.cpp
		$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<


%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<


