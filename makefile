SOURCES = src/main.cpp src/ising.cpp
EXEC = bin/ising.o

all: $(EXEC)

$(EXEC): $(SOURCES)
	g++ -o $(EXEC) $(SOURCES) -O3;
	$(EXEC)
