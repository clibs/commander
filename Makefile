test: test.c src/commander.c
	$(CC) $^ -std=c99 -o $@

unit: unit.c src/commander.c
	$(CC) $^ -std=c99 -o $@

clean:
	rm -f test unit

.PHONY: clean