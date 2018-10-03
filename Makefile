CFLAGS=-std=c11 -pedantic -Wall -Wextra -I source
source=source/basis.c source/evaluate.c source/funclist.c source/parser.c

test:
	gcc source/tests.c $(source) $(CFLAGS) -o test

MRFS:
	gcc source/MRFS.c $(source) $(CFLAGS) -o MRFS
