#
# 文件名称：makefile
# 摘要：    编译整个项目的makefile，不包括测试模块
#
# 当前版本：1.2
# 作者:	    KidLet
# 完成日期：2014年3月30日
#
# 历史:
# 	2014-2-17 首次编写
# 	2014-3-24 优化规则，分离为make.rules
# 	2014-3-30 添加编译选项 std=gnu++0x 来支持新特性 shared_ptr
#

CC          	=  gcc
CXX         	=  g++
CFLAGS      	+= -g -fPIC -Wno-deprecated -Wall -Werror -std=gnu++0x

SRC 			=  $(wildcard ./src/*.cpp)
OBJ 			=  $(patsubst %.cpp,%.o,$(SRC))
INCLUDE			=  -I./include
LIB				=  -lpthread -lgtest
LIB_DIR			=  -L./lib

EXE				=  KidHttpd

#------------------------------------------------------------------------------

all: $(EXE)

-include $(patsubst %.cpp,%.d,$(SRC))
-include ./make.rules

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o KidHttpd $(INCLUDE) $(LIB_DIR) $(LIB)

clean:
	@echo 'clean the project'
	@rm -f $(patsubst %.cpp,%.d,$(SRC))
	@rm -f $(patsubst %.cpp,%.o,$(SRC))
	@rm -f $(EXE)
.PHONY: clean

test:
	make -C ./test
.PHONY:	test




