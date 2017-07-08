all: see

OBJS = utils.o Window.o
LIBS =  -lmenu -lncurses
DEBUG = -g -Wall


ifeq ($(shell uname), Linux)
CXXFLAGS = -std=c++11
else
CXXFLAGS = -std=gnu++11
endif

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(DEBUG)

see: main.cpp $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(CXXFLAGS) $(DEBUG)

install:
	install -d /etc/see
	install -m 666 filter.conf /etc/see
	install -m 555 see /usr/bin/see

uninstall:
	rm -rf /etc/see/
	rm -f /usr/bin/see

clean:
	rm -f see $(OBJS)