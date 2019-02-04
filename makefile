CXX=g++
CXXFLAGS = -Wall -g -std=c++11

# Put object files in next line
OBJS = Memory.o ProgRegisters.o Sim.o Y86.o

# The OBJTEST macro is same as 'OBJS' above except replace Sim.o with testSim.o 
OBJTEST =  Memory.o ProgRegisters.o testSim.o Y86.o

#complete the following targest with appropriate dependencies and commands
yess:	$(OBJS) 
	$(CXX) $(OBJS) -o yess

ytest:  $(OBJTEST) $(CXX) $(OBJTEST) -o yess


#your object file targets below here...
Memory.o: Memory.cpp Memory.h
ProgRegisters.o: ProgRegisters.cpp ProgRegisters.h
Register.o: Register.h
Sim.o: Sim.cpp Sim.h
Y86.o: Y86.cpp Y86.h

# clean target
# Remeber, you don't want to delete your testSim.o file
# The following target preserves testSim.o
clean:
	cp testSim.o testSim-tmp
	rm *.o yess
	cp testSim-tmp testSim.o

