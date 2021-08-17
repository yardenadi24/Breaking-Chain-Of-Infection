# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
#LFLAGS  = -L/usr/lib

# All Targets
all: Assign1

# Tool invocations
#Executable
Assign1: bin/main.o bin/Agent.o bin/Graph.o bin/Session.o bin/Tree.o
	@echo 'Building target: Assign1'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/cTrace bin/main.o bin/Agent.o bin/Graph.o bin/Session.o bin/Tree.o
	@echo 'Finished building target: Assign1'
	@echo ' '

#Depends on the source and header files
bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

#Depends on the source and header files
bin/Agent.o: src/Agent.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Agent.o src/Agent.cpp

#Depends on the source and header files
bin/Graph.o: src/Graph.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Graph.o src/Graph.cpp

#Depends on the source and header files
bin/Session.o: src/Session.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Session.o src/Session.cpp

#Depends on the source and header files
bin/Tree.o: src/Tree.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Tree.o src/Tree.cpp

#CLean the build directory
clean:
	rm -f bin/*







































