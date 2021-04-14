CC = gcc

all : dynprog liblib.so staticprog

dynprog : main.c liblib.so asm.S
	gcc -O2 main.c asm.S -fno-omit-frame-pointer -Wl,-rpath,. -L. -llib -Wl,-Ttext-segment=1000 -odynprog

liblib.so : lib.c
	gcc -O2 lib.c -fPIC -DPIC -fno-omit-frame-pointer -shared -oliblib.so

staticprog : main.c lib.c asm.S
	gcc -O2 main.c lib.c asm.S -fno-omit-frame-pointer -ostaticprog

clean :
	-rm -f dynprog liblib.so staticprog
