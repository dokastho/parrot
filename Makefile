CXX = gcc

CXXFLAGS = -std=c99 -lm -Wall -Werror -g3 -lm
LINKFLAGS = -lm

squawk.o: parrot.c
	$(CXX) $(CXXFLAGS) -c $< -o squawk.o

parrot: main.c squawk.o
	$(CXX) $(CXXFLAGS) $^ $(LINKFLAGS) -o $@

clean:
	rm -rf *.o parrot
