CXX = c++
CFLAGS = -std=c++11
CCSOURCE = ${wildcards *.cpp}
CXXSOURCE = main.o cmdline.o Expr.o expTest.o Parse.o
HEADERS = ${wildcards *.h}
CXXFLAGS = --std=c++17 -O2
EXECUTABLE = ./msdscript

all: $(EXECUTABLE)

#run:
#	./msdscript --test

msdscript: $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) -o msdscript $(CXXSOURCE)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c  main.cpp

cmdline.o: cmdline.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c cmdline.cpp
	
Expr.o: Expr.cpp Expr.h
	$(CXX) $(CXXFLAGS) -c Expr.cpp

expTest.o: expTest.cpp expTest.h
	$(CXX) $(CXXFLAGS) -c expTest.cpp

Parse.o: Parse.cpp Parse.h
	$(CXX) $(CXXFLAGS) -c Parse.cpp
clean:
	rm -f *.o program
