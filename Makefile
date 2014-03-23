
test: test.c src/commander.c
	$(CC) $^ -o $@ -std=c89 -Wall -Wextra

clean:
	rm -f test

.PHONY: clean
