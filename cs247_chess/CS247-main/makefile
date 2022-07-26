CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = final
OBJECTS = main.o board.o piece.o cell.o move.o runner.o change.o player.o game.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

all: ./final

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
