CC = gcc
CFLAGS = -Wall -Werror -m32 -std=gnu11

BINS = introspect mainfile sofile.so usemem

all : $(BINS)

usemem : usemem.c

introspect : introspect.c
	$(CC) $(CFLAGS) -rdynamic $^ -o$@ -ldl

mainfile : mainfile.c
	$(CC) $(CFLAGS) -rdynamic $^ -o$@ -ldl

sofile.so : sofile.c
	$(CC) $(CFLAGS) -fPIC -DPIC -shared $^ -o$@

clean :
	-rm -f $(BINS)
