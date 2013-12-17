
test: test.c src/commander.c
	$(CC) $^ -std=c99 -o $@ -Wall -Wextra

clean:
	rm -f test

.PHONY: clean
