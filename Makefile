CXX = c++
CFLAGS = -std=c++11
CCSOURCE = ${wildcards *.cpp}
CXXSOURCE = main.o cmdline.o Expr.o expTest.o Parse.o val.o
HEADERS = ${wildcards *.h}
CXXFLAGS = -fsanitize=undefined -fno-sanitize-recover=undefined --std=c++17 -O2
EXECUTABLE = ./msdscript

otherEXECUTABLE = test_msdscript.o exec.o

all: $(EXECUTABLE)

#run:
#	./msdscript --test

msdscript: $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) -o msdscript $(CXXSOURCE)

test_msdscript: $(otherEXECUTABLE)
	$(CXX) $(CXXFLAGS) -o test_msdscript $(otherEXECUTABLE)

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

test_msdscript.o: test_msdscript.cpp test_msdscript.h
	$(CXX) $(CXXFLAGS) -c test_msdscript.cpp

exec.o: exec.cpp exec.h
	$(CXX) $(CXXFLAGS) -c exec.cpp

val.o: val.cpp val.h
	$(CXX) $(CXXFLAGS) -c val.cpp


clean:
	rm -f *.o msdscript
