CXXFLAGS =	-O2 -g -Wall -I../stk/include -D__OS_MACOSX__ -fmessage-length=0

LIBS =	../stk/lib/*

all: gaincontrol dadsr dsine dmultisine

clean:
	rm -f gaincontrol.o gaincontrol \
    dsine.o dsine \
    dadsr.o dadsr \
    dmultisine.o dmultisine 

dadsr:	dadsr.o
	$(CXX) -o dadsr dadsr.o $(LIBS)

dsine:	dsine.o
	$(CXX) -o dsine dsine.o $(LIBS)

dmultisine:	dmultisine.o
	$(CXX) -o dmultisine dmultisine.o $(LIBS)

gaincontrol: gaincontrol.o
	$(CXX) -o gaincontrol gaincontrol.o $(LIBS)

