INC=inc
CC=gcc
CFLAGS=-Wall -pedantic -g

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main
LIBS=-lm

LIBDIR=lib
LIB=$(LIBDIR)/libarary.a

# testing
TEST=tests
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

all: $(LIB)

$(LIB): $(LIBDIR) $(OBJ) $(OBJS)
	ar -crvs $(LIB) $(OBJS)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(TEST)/bin/%: $(TEST)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ $(LIBS) -lcriterion

$(TEST)/bin:
	mkdir $@

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

test: $(LIB) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	rm -f $(OBJ)/*.o $(BINDIR)/* $(TEST)/bin/* $(LIBDIR)/*.a

debug:
	gdb bin/main