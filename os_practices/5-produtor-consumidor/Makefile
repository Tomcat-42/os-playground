CC :=gcc
CFLAGS := -O3

SRC = $(wildcard *.c)
BIN = $(patsubst %.c,%,$(SRC))

all: $(BIN)

clean:
	$(RM) $(BIN)
