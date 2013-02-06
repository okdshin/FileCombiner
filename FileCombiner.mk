CXX = g++ -std=gnu++0x
CXXFLAGS = -Wall -g -D FILECOMBINER_UNIT_TEST
INCLUDES = 
LIBS = -lboost_system -lboost_filesystem
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
