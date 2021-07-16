CC=gcc
BIN=example
OBJS=queue.o

all: $(BIN)

%.o: %.c %.h
	$(CC) -c $< -o $@

%.o: %.c
	$(CC) $^ -o $@

$(BIN): $(BIN).c $(OBJS)
	$(CC) $^ -o $@

clean:
	rm *.exe *.o
