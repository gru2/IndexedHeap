
OPT_FLAGS = -g

CPPFLAGS = $(OPT_FLAGS) -I.

TARGETS = IndexedHeapTest

all: $(TARGETS)

IndexedHeapTest: IndexedHeapTest.o
	g++ -o IndexedHeapTest IndexedHeapTest.o

%.o: %.cpp
	g++ -c $(CPPFLAGS) $< -o $@

clean::
	-rm -vf $(TARGETS) *.o
