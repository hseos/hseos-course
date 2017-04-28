CC = gcc
CFLAGS = -O2 -g -Wall -Werror -std=gnu11 -pthread

SRCS = $(wildcard *.c)
EXES = $(SRCS:.c=)

all : $(EXES)

clean :
	-rm -f $(EXES)
