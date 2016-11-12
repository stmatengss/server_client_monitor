
ROOT= $(shell pwd)
OUTPUTS= bin/driver bin/gen bin/test bin/gen-mass
DEFAULT= default

CXX?= g++
CXXFLAGS?= -O3 -std=c++11 -pthread -g -I$(ROOT)
CXXFLAGS2?= -std=c++11 -g -fopenmp -I$(ROOT)
CXXFLAGS3?= -O3 -std=c++11 -g -fopenmp -I$(ROOT)
HEADERS= $(shell find . -name '*.hpp')

all: $(DEFAULT) $(OUTPUTS)

bin/driver: benchmark/driver.cpp $(HEADERS) 
	$(CXX) $(CXXFLAGS) -o $@ $< $(SYSLIBS)

bin/gen: tools/gen-dataset.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SYSLIBS)

bin/gen-mass: tools/gen-mass-dataset.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SYSLIBS)

bin/test: test/testFunc.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SYSLIBS)

default:
	mkdir -p ./bin
clean:
	rm -rf $(OUTPUTS)
run_test:
	./bin/test
run_gen:
	./bin/gen-mass -o test -n 100000

