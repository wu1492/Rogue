# suffix rules don't allow pre-requisites to be used and are deprecated for
# this reason.  The right way to do this is to use patterns.  The "%" pattern
# allows any file to be matched.
OBJS = 
CC = g++
INCLUDE = -lxerces-c
LIBS = 
CFLAGS = -g -I ./src/xerces-c-3.1.1-x86_64-linux-gcc-3.4/include/ -L  ./src/xerces-c-3.1.1-x86_64-linux-gcc-3.4/lib/ 
EXECUTABLE = Test
COMMANDLINE = 
TEST = *.xml
OUT= Test

PATH_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

.PHONY : 
run : $(EXECUTABLE)
	./$(EXECUTABLE) $(MAKECMDGOALS)

cleanmake : clean Step1


%.xml:
	$(CC) $(CFLAGS) ./src/*.cpp -o $(EXECUTABLE) $(OBJS) $(INCLUDE) $(LIBS)
	./$(EXECUTABLE) $(MAKECMDGOALS)

.PHONY : $(EXECUTABLE)
$(EXECUTABLE) :  $(OBJS)
	$(CC) $(CFLAGS) ./src/*.cpp -o $(EXECUTABLE) $(OBJS) $(INCLUDE) $(LIBS)



%.o : %.c
	$(CC) $(CFLAGS) -c $@ $(INCLUDE) $(LIBS)

clean :
	rm $(EXECUTABLE) ${OBJS} 
