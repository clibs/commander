
test: test.c src/commander.c
	$(CC) $^ -o $@ -Wall -Wextra

clean:
	rm -f test

.PHONY: clean
