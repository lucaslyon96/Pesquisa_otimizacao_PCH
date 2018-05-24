EXE = minimiza

CCC = g++
CCOPT = -O4 -fPIC -fexceptions -DNDEBUG -DIL_STD -Wno-deprecated

#CPLEXDIR      = /home/cplex/cplex
#CONCERTDIR    = /home/cplex/concert


#máquina SINFO------------------------------------------------------------------------------------

CPLEXDIR      = /opt/ibm/ILOG/CPLEX_Studio1261/cplex
CONCERTDIR    = /opt/ibm/ILOG/CPLEX_Studio1261/concert

CPLEXLIBDIR   = $(CPLEXDIR)/lib/x86-64_linux/static_pic/
CONCERTLIBDIR = $(CONCERTDIR)/lib/x86-64_linux/static_pic/
#máquina SINFO
CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -m64 -lm -lpthread
#------------------------------------------------------------------------------------------------


#máquina lab------------------------------------------------------------------------------------
#CPLEXLIBDIR   = $(CPLEXDIR)/lib/x86-64_sles10_4.1/static_pic
#CONCERTLIBDIR = $(CONCERTDIR)/lib/x86-64_sles10_4.1/static_pic
#máquina lab
#CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -m64 -lm -lpthread
#------------------------------------------------------------------------------------------------

#------------------------------------------------------------------------------------------------
#máquina ECT
#CPLEXLIBDIR   = $(CPLEXDIR)/lib/x86_sles10_4.1/static_pic
#CONCERTLIBDIR = $(CONCERTDIR)/lib/x86_sles10_4.1/static_pic
#máquina ect
#CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -lm -lpthread
#------------------------------------------------------------------------------------------------




CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR)

OBJS    = minimiza.o

$(EXE): $(OBJS)
	$(CCC) $(CCFLAGS) -o $(EXE) $(OBJS) $(CCLNFLAGS)

minimiza.o: minimiza.cpp
	$(CCC) -c $(CCFLAGS) minimiza.cpp


clean:
	rm *.o

del:
	rm *.o $(EXECUTABLE) *.log *~
	touch *

