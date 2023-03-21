CCOPT = -m64 -O3 -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD -std=c++11

SYSTEM = x86-64_osx
LIBFORMAT = static_pic
CPLEXLIB = cplex$(dynamic:yes=1290)

CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXINCDIR = $(CPLEXDIR)/include
CONCERTINCDIR = $(CONCERTDIR)/include
CCFLAGS = $(CCOPT) -I $(CPLEXINCDIR) -I $(CONCERTINCDIR)
CCLNDIRS = -L $(CPLEXLIBDIR) -L $(CONCERTLIBDIR) $(dynamic:yes=-L $(CPLEXBINDIR))
CCLNFLAGS = -lconcert -lilocplex -l $(CPLEXLIB) -lm -lpthread -ldl

GCC_FLAGS=-std=c++11 -O3

make: utils.o cplex.o main.cpp
	g++ $(CCFLAGS) $(CCLNDIRS) main.cpp cplex.o utils.o -o main.out $(CCLNFLAGS)

cplex.o: cplex.cpp cplex.h
	g++ -c $(CCFLAGS) cplex.cpp -o cplex.o

utils.o: ../utils/utils.cpp ../utils/utils.h
	g++ $(GCC_FLAGS) -c ../utils/utils.cpp 

clean:
	rm -rf *.o *.out