SOURCES = src/main.cpp src/ising.cpp src/func.cpp
EXEC = bin/ising.o
LIBS = src/ising.cpp src/func.cpp
T_CRIT_SOURCES = src/main_T_crit.cpp
T_CRIT_EXEC = bin/T_crit.o

all: $(EXEC)
t_crit: $(T_CRIT_EXEC)

$(EXEC): $(SOURCES)
	g++ -o $(EXEC) $(SOURCES) $(LIBS) -O3;
	$(EXEC)

$(T_CRIT_EXEC): $(T_CRIT_SOURCES)
	g++ -o $(T_CRIT_EXEC) $(T_CRIT_SOURCES) $(LIBS) -O3;
	$(T_CRIT_EXEC)
