LIBS = src/ising.cpp src/func.cpp
T_CRIT_SOURCES = src/main_T_crit.cpp
T_CRIT_EXEC = bin/T_crit.o
FINITE_SOURCES = src/main_finite.cpp
FINITE_EXEC = bin/finite.o
EVO_SOURCES = src/main_evolution.cpp
EVO_EXEC = bin/evolution.o
CORR_SOURCES = src/main_correlation.cpp
CORR_EXEC = bin/correlation.o

t_crit: $(T_CRIT_EXEC)
finite: $(FINITE_EXEC)
evo: $(EVO_EXEC)
correlation: $(CORR_EXEC)

$(T_CRIT_EXEC): $(T_CRIT_SOURCES)
	g++ -o $(T_CRIT_EXEC) $(T_CRIT_SOURCES) $(LIBS) -O3;
	$(T_CRIT_EXEC)

$(FINITE_EXEC): $(FINITE_SOURCES)
	g++ -o $(FINITE_EXEC) $(FINITE_SOURCES) $(LIBS) -O3;
	$(FINITE_EXEC)

$(EVO_EXEC): $(EVO_SOURCES)
	g++ -o $(EVO_EXEC) $(EVO_SOURCES) $(LIBS) -O3;
	$(EVO_EXEC)

$(CORR_EXEC): $(CORR_SOURCES)
	g++ -o $(CORR_EXEC) $(CORR_SOURCES) $(LIBS) -O3;
	$(CORR_EXEC)
