#Monica Liu, mfl4an
#Bethany Connor, bac5rc
#Catherine Dworak, cfd7kv
#CS 4810 Project 
#Makefile
CXX = clang++
CXXFLAGS = -Wall
LIBS = -lglut -lGL -lGLU -lm
OFILES = maze.o
.SUFFIXES = .o .cpp

main: $(OFILES)
	$(CXX) $(CXXFLAGS) $(LIBS) $(OFILES)
clean:
	/bin/rm -f *.o *~