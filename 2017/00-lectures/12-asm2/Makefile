CC = gcc
CFLAGS = -m32 -std=gnu11 -g -Wall -Werror
TARGETS = printflags printflags2 add cmp div fixretaddr getloc mul varuse
ASFLAGS = -m32 -g

all : $(TARGETS)

add : add.S simpleio_x86.S
cmp : cmp.S simpleio_x86.S
div : div.S simpleio_x86.S
fixretaddr : fixretaddr.S simpleio_x86.S
getloc : getloc.S simpleio_x86.S
mul : mul.S simpleio_x86.S
varuse : varuse.S simpleio_x86.S

clean :
		-rm -f $(TARGETS)
