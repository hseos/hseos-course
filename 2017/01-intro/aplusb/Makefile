CC = gcc
CFLAGS = -Wall -Werror -std=gnu11 -O2 -g
TARGET = hello
SHELL = /bin/bash

all : $(TARGET)

$(TARGET) : $(TARGET).c

testing : hello
	cd tests; ./run.sh

clean :
	-rm -f $(TARGET)
