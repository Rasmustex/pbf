CC=clang
CFLAGS=-g -Wall
INCLUDE=include
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=$(BINDIR)/pbf
INSTALLDIR=/usr/bin

all:$(BIN)

release: CFLAGS=-O2 -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/pbf.h | dirsetup
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) -r $(BINDIR)/* $(OBJ)/*

install: release 
	cp $(BIN) $(INSTALLDIR)

dirsetup: 
	mkdir -p $(BINDIR) $(OBJ) 