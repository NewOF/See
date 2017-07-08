all: see

OBJS = utils.o Window.o
LIBS =  -lmenu
DEBUG = -g -Wall


ifeq ($(shell uname), Linux)
LIBS += -lcurses
CXXFLAGS = -std=c++11
else
LIBS +=  -lncurses
CXXFLAGS = -std=gnu++11
endif

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(DEBUG) $< -o $@

see: main.cpp $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(DEBUG) $(CXXFLAGS)

install:
	install -d /etc/search
	install -m 666 filter.conf /etc/search
	install -m 555 se /usr/bin/se

clean:
	rm -f see $(OBJS)