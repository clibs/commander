CC = gcc

test: test.c src/commander.c
	$(CC) -Wall $^ -std=c99 -o $@

unit: unit.c src/commander.c
	$(CC) -Wall -g -fprofile-arcs -ftest-coverage $^ -std=c99 -o $@

clean:
	rm -f test

.PHONY: clean