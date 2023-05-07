all:
	clang -fsanitize=address -g -o testsched test_scheduling.c scheduling.c
clean:
	rm -i testsched
