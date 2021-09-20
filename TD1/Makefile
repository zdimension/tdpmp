#=======================================================================
# Basic C++: makefile example to use as a reminder or as a template
#-----------------------------------------------------------------------
# Julien DeAntoni --- No Copyright 2016
# $Id: convenient Makefile but muist be tuned for templated project 
#      v0.2 2016/09/06
#=======================================================================

#only ok for project with no templated classes

#compiler
COMPILER = g++-9
#linker
LINKER =g++-9

#options for linker and compiler
FLAGS =-g -ansi -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -D_DEBUG_ -std=c++11

EXE_NAME= palindrome.exe

#can have several ones separated by spaces, only cpp files
SOURCES = main_palindrome.cpp myUtils.cpp 


#PATH to extra header used in the project (when using libs not installed in the OS)
INC_PATHS= -I

#extra libs used in the project (for instance -lpthread)
LIBS	= -L 

LINKOBJ	= $(SOURCES:.cpp=.o)
SOURCEHEADERS = $(SOURCES:.cpp=.h)

$(EXE_NAME): $(LINKOBJ)
	$(LINKER) $(LINKOBJ) $(INC_PATHS) $(LIBS) -o $(EXE_NAME) $(FLAGS)

%.o: %.cpp %.h
	$(COMPILER) -g -c $< -o $@ $(INC_PATHS) $(FLAGS)

%.o: %.cpp 
	$(COMPILER) -g -c $< -o $@ $(INC_PATHS) $(FLAGS)
	
# cleanup
clean:
	rm -f $(LINKOBJ)

