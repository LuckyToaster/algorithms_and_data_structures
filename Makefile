#COMPILER := g++
FLAGS := -Wall -Wextra
SRCS := $(wildcard src/*.cpp)
TARGETS := $(patsubst src/%.cpp,build/%,$(SRCS))
EXECUTABLES := $(wildcard build/*)

.PHONY: run clean 

# Default rule, this is placed first and will execute the next rule it encounters
all: $(TARGETS)

build/%: src/%.cpp | build
	g++ $(FLAGS) $< -o $@

build:
	mkdir -p build

run: $(EXECUTABLES)
	@for target in $(EXECUTABLES); do \
		$$target; \
    done

clean:
	rm -rf build

sorting: src/sorting/sorting_test.cpp
	@mkdir -p build
	g++ $(FLAGS) $^ -o build/$@

linkedlist: src/linkedlist/linkedlist.cpp src/linkedlist/linkedlist_test.cpp
	@mkdir -p build
	g++ $(FLAGS) $^ -o build/$@
