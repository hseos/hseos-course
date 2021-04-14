# Target named 'first' is just a link to another target.
# By default make builds first target if not specified
first: program.jpg

# Good style (but horror for really big projects) is to use separate
# targets for each source files. For big project it is better not
# to use hand-written Makefile, but use Makefile generators
# like 'cmake' or 'qmake'

# Syntax:
#
# Target: Space-separated list of dependencies
# \t   Command1
# \t   Command2 etc.
# NOTE on \t symbol! Use good text editors like 'vim' or 'emacs' to
# ensure that Tab button inserts '\t' but not spaces in Makefile-mode
# Note that dependencies list should contain not just source, but used
# header files too.
file1.o: file1.c heads.h
    # It is better to use macro-variables $(CC), $(CXX) etc. to
	# be cross-platform
	$(CC) $(CFLAGS) -c file1.c

file2.o: file2.c heads.h
	$(CC) $(CFLAGS) -c file2.c

file3.o: file3.cpp heads.h
	$(CXX) $(CXXFLAGS) -c file3.cpp

# Program linkage stage
program.jpg: file1.o file2.o file3.o
	$(CXX) $(LDFLAGS) -o program.jpg file1.o file2.o file3.o

# Useful target to delete temporary files
clean:
	rm *.o

# Target to perform trivial testing
test: program.jpg test.txt standard.txt
	# Execute program, pass testing data to it's
	# STDIN and write output to some temporary file
	./program.jpg <test.txt >out.txt
	# Compare output data to some hand-written (or generated and
	# verified) standard output
	diff out.txt standard.txt
	# On failure the following will not be executed
	echo "All OK!"
	# Delete temporary file
	rm out.txt
