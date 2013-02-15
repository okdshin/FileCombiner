CXX = g++ -std=gnu++0x
CXXFLAGS = -Wall -g -D FILECOMBINER_UNIT_TEST
INCLUDES = -IC:\MinGW\msys\1.0\home\okada\boost_1_52_0
LIBS = -LC:\MinGW\msys\1.0\home\okada\boost_1_52_0\stage\mingw\lib -lboost_system-mgw47-mt-sd-1_52 -lboost_filesystem-mgw47-mt-sd-1_52
OBJS = FileCombiner.o
PROGRAM = FileCombiner.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
