CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -g -Werror=delete-non-virtual-dtor --coverage

# Choose main file: testingMain or DemoMain (default: testingMain)
MAIN_FILE ?= testingMain

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
EXEC := main
VALGRIND_OUT := valgrind_output.txt
VALGRIND_LOG := valgrind.txt
COVERAGE_OUT := coverage_output.txt
COVERAGE_LOG := coverage.txt

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --keep-stacktraces=alloc-and-free --error-exitcode=1 --log-file=valgrind.txt ./$(EXEC) 2>&1 | tee $(VALGRIND_OUT)

gdb: $(EXEC)
	gdb ./$(EXEC)

coverage: $(EXEC)
	./$(EXEC) > $(COVERAGE_OUT) 2>&1 || true
	# Run gcov (produce human-readable coverage report). Use the source basename(s).
	gcov -f -m -r -j ${filesInCoverageReport} > $(COVERAGE_LOG) || true
	# Generate an HTML report (optional, requires gcovr installed)
	-gcovr --exclude 'doctest.h' --gcov-ignore-parse-errors negative_hits.warn --html-details -o output.html || true

.PHONY: coverage

clean:
	rm *.o *.gcov *.gcda *.gcno *.gz *.html *.css $(COVERAGE_OUT) $(COVERAGE_LOG) $(VALGRIND_OUT) $(VALGRIND_LOG) $(EXEC) -f ${files}