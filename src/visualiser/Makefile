CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99 # $(foreach lib, $(LIBS), -I$(lib))
#LIBS =
LDFLAGS = $(CFLAGS)
BUILD = test
#LDLIBS = $(foreach lib, $(LIBS), -L$(lib) -l$(lib))
TEST_DFS_ONE_STEP_DEPENDENCIES = test_dfs_one_step.o utils.o dfs_one_step.o
TEST_UNDIRECTED_INITIALISE_DEPENDENCIES = utils.o undirected_graph.o test_undirected_initialise.o 

all:	$(BUILD)

main:	main.o

test_dfs_one_step:	$(TEST_DFS_ONE_STEP_DEPENDENCIES)
	$(CC) $(CFLAGS) $(TEST_DFS_ONE_STEP_DEPENDENCIES) -o test

test_ud_init:	$(TEST_UNDIRECTED_INITIALISE_DEPENDENCIES)
	$(CC) $(CFLAGS) $(TEST_UNDIRECTED_INITIALISE_DEPENDENCIES) -o test_ud_init

#libs:
#	$(foreach lib, $(LIBS), cd $(lib); make; cd ..;)

clean:
	rm -f *.o
	rm -f *.a
	rm -f $(BUILD)
#	$(foreach lib, $(LIBS), cd $(lib); make clean; cd ..;)

.PHONY: all clean test_dfs_one_step test_ud_init #libs

test_undirected_initialise.o:	undirected_graph.h	

test_dfs_one_step.o:	dfs_one_step.h utils.h

undirected_graph.o:	undirected_graph.h utils.h

dfs_one_step.o:	dfs_one_step.h

utils.o:	utils.h
