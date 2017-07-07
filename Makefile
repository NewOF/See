all: search

OBJS = utils.o Window.o
LIBS =  -lmenu
DEBUG = -g -Wall
CXXFLAGS = -std=c++11

ifeq ($(shell uname), Linux)
LIBS += -lcurses
else
LIBS +=  -lncurses
utils.o: utils.cpp
	$(CXX) -c $< -o $@ $(DEBUG)
endif

$(OBJS): utils.h Window.h

search: main.cpp $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(DEBUG)

install:
	

clean:
	rm -f search $(OBJS)