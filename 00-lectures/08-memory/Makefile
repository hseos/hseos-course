CC = gcc
CFLAGS = -Wall -O2 -std=gnu11 -D_FILE_OFFSET_BITS=64

TARGETS = mmap1 mmap2 mmap3 mmap4 mmap5 mmap6 dynprintf.so

all : $(TARGETS)

mmap1 : mmap1.c
mmap2 : mmap2.c
mmap3 : mmap3.c
mmap4 : mmap4.c
mmap5 : mmap5.c
mmap6 : mmap6.c

dynprintf.so : dynprintf.c
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

clean:
	-rm -f $(TARGETS)
