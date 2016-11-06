
all : dllib.so dluser dllib2.so

clean :
	-rm -f dllib.so dluser

dllib.so : dllib.c
	gcc -shared -O2 -fPIC dllib.c -o dllib.so
dllib2.so : dllib2.cpp
	g++ -shared -O2 -fPIC dllib2.cpp -o dllib2.so

dluser : dluser.c
	gcc -g -O2 dluser.c -o dluser -ldl
