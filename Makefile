
test: test.c src/commander.c
	$(CC) $^ -o $@ -Wall -Wextra
	./test test1 -v --required important
	./test test2 --optional justsoso
	./test test3 ex1 ex2 ex3

clean:
	rm -f test

.PHONY: clean
