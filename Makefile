CXX=clang++
# CXX=g++

# Compiler flags for development
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

# For final submission (treat warnings as errors)
# CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

BINARIES=testWordCount

all: ${BINARIES}

# Target for the main test binary
testWordCount: tddFuncs.o WordCount.o Lab07Test01.o
	${CXX} $^ -o $@

# Convenience target to run tests
tests: ${BINARIES}
	./testWordCount

# Clean up generated files
clean:
	/bin/rm -f ${BINARIES} *.o