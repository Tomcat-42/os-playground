CC :=gcc
CFLAGS :=

SRC = $(wildcard *.c)
BIN = $(patsubst %.c,%,$(SRC))

all: $(BIN)

clean:
	$(RM) $(BIN)
