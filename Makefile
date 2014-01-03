# Makefile
# Copyright 2013 Alexandre Boucey <alexandre.boucey@alumni.univ-avignon.fr>
CXXFLAGS+=-W -Wall -Wextra -pedantic -std=c++1y -O3
LDFLAGS=
EXEC=APC
HEADERS_DIR=headers
SRC= $(wildcard src/*.cpp)
HEADERS= $(wildcard ${HEADERS_DIR}/*.h)
OBJ= $(addprefix obj/, $(notdir $(SRC:.cpp=.o)))

all: init compile

debug: CXXFLAGS+= -g
debug: init compile

build: $(OBJ)
compile: $(EXEC)

format:
	astyle -A01 -k3 -n $(HEADERS) $(SRC)

$(EXEC): $(OBJ)
	${CXX} ${LDFLAGS} -o bin/$@ $^

obj/main.o: $(HEADERS)

obj/%.o: src/%.cpp
	${CXX} ${CXXFLAGS} -c -I${HEADERS_DIR} -o $@ $<

init:
	@echo "Using ${CXX}"
	mkdir -p obj bin

.PHONY: clean mrproper

clean:
	rm -rf obj

mrproper: clean
	rm -rf bin
