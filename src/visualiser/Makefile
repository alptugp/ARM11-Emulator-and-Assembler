CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99 # $(foreach lib, $(LIBS), -I$(lib))
#LIBS =
LDFLAGS = $(CFLAGS)
BUILD = test
#LDLIBS = $(foreach lib, $(LIBS), -L$(lib) -l$(lib))
TEST_DEPENDENCIES = unit_tests.o utils.o dfs_one_step.o

all:	$(BUILD)

main:	main.o

test:	$(TEST_DEPENDENCIES)
	$(CC) $(CFLAGS) $(TEST_DEPENDENCIES) -o test

#libs:
#	$(foreach lib, $(LIBS), cd $(lib); make; cd ..;)

clean:
	rm -f *.o
	rm -f *.a
	rm -f $(BUILD)
#	$(foreach lib, $(LIBS), cd $(lib); make clean; cd ..;)

.PHONY: all clean test #libs

unit_tests.o:	undirected_graph.h

# undirected_graph.o:	undirected_graph.h

dfs_one_step.o:	dfs_one_step.h

utils.o:	utils.h