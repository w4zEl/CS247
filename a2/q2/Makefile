CXX=g++
CXXFLAGS=-std=c++14 -pedantic -Wall -Wextra -g -MMD
EXEC=a2q2
CCFILES=$(wildcard *.cc)
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
