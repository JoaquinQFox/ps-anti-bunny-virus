CC = gcc

SRC = src/detector/main.c src/monitor/monitor.c src/detector/detector.c
# SRC = src/monitor/main.c src/monitor/monitor.c src/detector/detector.c
BIN = anti_bunny

all:
	$(CC) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)
