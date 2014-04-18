#Monica Liu, mfl4an
#Bethany Connor, bac5rc
#Catherine Dworak, cfd7kv
#CS 4810 Project 
#Makefile
CXX = g++
CXXFLAGS = -Wall
LIBS = -lglut -lGL -lGLU 
OFILES = maze.o
.SUFFIXES = .o .cpp

main: $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) $(LIBS)
clean:
	/bin/rm -f *.o *~
