CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -g -Werror=delete-non-virtual-dtor $(shell pkg-config --cflags gtkmm-3.0)
LDLIBS := $(shell pkg-config --libs gtkmm-3.0)

# Choose main file: testingMain or DemoMain (default: testingMain)
MAIN_FILE ?= DemoMain

# Get all .cpp files, then exclude the main file we're NOT using
ALL_CPP := $(wildcard *.cpp)
ifeq ($(MAIN_FILE),testingMain)
    EXCLUDE := DemoMain.cpp
else ifeq ($(MAIN_FILE),DemoMain)
    EXCLUDE := testingMain.cpp
else
    $(error Invalid MAIN_FILE. Use 'testingMain' or 'DemoMain')
endif

SRC := $(filter-out $(EXCLUDE),$(ALL_CPP))
OBJ := $(SRC:.cpp=.o)
filesInCoverageReport = testingMain
EXEC := $(MAIN_FILE)
VALGRIND_OUT := valgrind_output.txt
VALGRIND_LOG := valgrind.txt
COVERAGE_OUT := coverage_output.txt
COVERAGE_LOG := coverage.txt

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --keep-stacktraces=alloc-and-free --error-exitcode=1 --log-file=$(VALGRIND_LOG) ./$(EXEC) 2>&1 | tee $(VALGRIND_OUT)

gdb: $(EXEC)
	gdb ./$(EXEC)

coverage: $(OBJ)
	$(MAKE) clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) --coverage" all
	./$(EXEC) > $(COVERAGE_OUT) 2>&1 || true
	gcov -f -m -r -j ${filesInCoverageReport} > $(COVERAGE_LOG) || true
	-gcovr --exclude 'doctest.h' --html-details -o output.html || true

.PHONY: coverage clean

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.gz *.html *.css $(COVERAGE_OUT) $(COVERAGE_LOG) $(VALGRIND_OUT) $(VALGRIND_LOG) $(EXEC)
