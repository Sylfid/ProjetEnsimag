PROG = calc
OBJS = calc.o stack.o
CXX = g++
CXXFLAGS = -Wall -g -pedantic

all: test

test: 
	g++ Test.cpp DVector.cpp -o main.out
run: 
	./main.out
clean:
	rm *.o

$(PROG): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS)
