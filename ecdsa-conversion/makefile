all: convert test
convert: convert.c
	gcc -Wall -Wextra -O2 -o convert convert.c

test: convert
	./test.sh

clean:
	rm -f convert sig-* key-*
