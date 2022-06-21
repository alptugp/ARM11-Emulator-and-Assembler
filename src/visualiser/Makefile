CC = gcc
CFLAGS = -g -Wall -pedantic -std=c99 # $(foreach lib, $(LIBS), -I$(lib))
#LIBS =
LDFLAGS = $(CFLAGS)
#LDLIBS = $(foreach lib, $(LIBS), -L$(lib) -l$(lib))

all:	main

main:	main.o

#libs:
#	$(foreach lib, $(LIBS), cd $(lib); make; cd ..;)

clean:
	rm -f *.o
	rm -f *.a
	rm -f $(BUILD)
#	$(foreach lib, $(LIBS), cd $(lib); make clean; cd ..;)

.PHONY: all clean #libs

main.o:	utils.h