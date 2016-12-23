#=============================================
#
# object := $(wildcard *.o) .o结尾字符集
# -$(subst output,,$@) 截取字符串的意思
# $@:目前规则中所有的目标的集合
# $<:所有的依赖目标集
# $(filter %.o, $(files)):模式中为".o"的内容
#=============================================

VPATH = code:./code/include:./code/api/apiimpl:./code/api/include/

LIBS = -lm
OBJS = main.o IDateApiImpl.o
CFLAGS = -Wall

SRCS = code/main.c code/api/apiimpl/IDateApiImpl.c
INC = -I./code/include -I./code/api/include

edit: ${OBJS};
	gcc -o edit ${OBJS} ${LIBS}
	@echo 正在编译......

.PHONY : clean
clean:
	rm -f edit ${OBJS}

%.o:%.c
	gcc -Wall $(INC) -o $@ -c $<
