#this Makefile goes in the src directory

EXECUTABLE := StudentAndFacultyDatabase

# the source files to be built
SOURCES := *.cpp

INCLUDES := -I ../include
EXT := exe
CC := g++

#the command given to run an executable
RUNCOMMAND := ./

#compiles the source files into an executable
all:
	$(CC) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE).$(EXT)

#runs the executable
#$(file) will allow the user to pass in a command line argument using make run arg1=the name of the file the user wants to pass in
run:
	$(RUNCOMMAND)$(EXECUTABLE).$(EXT)

#deletes any files that are not a source file
realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;

# this line required by make - don't delete
