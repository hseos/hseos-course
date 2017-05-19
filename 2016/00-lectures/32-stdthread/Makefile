CC = gcc
CFLAGS = -O2 -g -Wall -Werror -std=gnu11 -pthread
CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=gnu++17 -pthread

SRCS = $(wildcard *.cpp)
EXES = $(SRCS:.cpp=)

all : $(EXES)

clean :
	-rm -f $(EXES)
