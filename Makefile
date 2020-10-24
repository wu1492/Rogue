# suffix rules don't allow pre-requisites to be used and are deprecated for
# this reason.  The right way to do this is to use patterns.  The "%" pattern
# allows any file to be matched.
OBJS = ./src/main.o ./src/GridChar.o ./src/Action.o ./src/Armor.o ./src/BlessCurseOwner.o ./src/ChangedDisplayedType.o ./src/Creature.o ./src/CreatureAction.o ./src/Displayable.o ./src/DropPack.o ./src/Dungeon.o ./src/DungeonXMLHandler.o ./src/EndGame.o ./src/Hallucinate.o ./src/Item.o ./src/ItemAction.o ./src/Monster.o ./src/ObjectDisplayGrid.o ./src/Passage.o ./src/Player.o ./src/Remove.o ./src/Room.o ./src/Scroll.o ./src/Structure.o ./src/Sword.o ./src/Teleport.o ./src/UpdateDisplay.o ./src/YouWin.o
CC = g++
INCLUDE = -lxerces-c -lncurses -lpthread
LIBS = 
CFLAGS = -g -I ./src/xerces-c-3.1.1-x86_64-linux-gcc-3.4/include/ -L  ./src/xerces-c-3.1.1-x86_64-linux-gcc-3.4/lib/ 
EXECUTABLE = Test
COMMANDLINE = 
HEADERS = $(CLASSES:.cpp=.h)
TEST = *.xml
OUT= Test
SRC_DIR = ./src

PATH_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

.PHONY : 
run : $(EXECUTABLE)
	./$(EXECUTABLE) $(MAKECMDGOALS)

cleanmake : clean Step1


%.xml: $(OBJS)
	$(CC)  $(CFLAGS) -o $(EXECUTABLE) $(OBJS) $(INCLUDE) $(LIBS)
	./$(EXECUTABLE) $(MAKECMDGOALS)

.PHONY : $(EXECUTABLE)
$(EXECUTABLE) :  $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS) $(INCLUDE) $(LIBS)



./src/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm $(EXECUTABLE) ${OBJS} 
