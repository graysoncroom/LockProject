CC=g++                            # compiler
CFLAGS=-std=c++11 -Wall -Wextra   # compiler flags
LDFLAGS=-pthread                  # linker flags

SRC = mutual.cpp                  # source file
EXE = mutual                      # executable file

all: $(EXE)                  # build the executable

$(EXE): $(SRC)               # rule to compile into exe
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(EXE)

clean:                       # cleanup generated stuff rule
	rm -f $(EXE)
