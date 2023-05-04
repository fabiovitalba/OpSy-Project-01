all:
	clang -g -o testsched test_scheduling.c scheduling.c
clean:
	rm -i testsched
