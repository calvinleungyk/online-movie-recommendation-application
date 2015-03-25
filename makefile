# Detecting OS
UNAME_S=$(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CC=g++-4.8
    GTEST_LL=-I /usr/local/opt/gtest/include/ -lgtest_main -lpthread
else
    ifeq ($(UNAME_S),Darwin)
        CC=g++
        GTEST_LL=-I /usr/local/opt/gtest/include/ -L /usr/local/opt/gtest/lib/ -lgtest_main -lgtest -lpthread
    else
        CC=g++
        GTEST_LL=-I /usr/local/opt/gtest/include/ -L /usr/local/lib/ -lgtest_main -lgtest -lpthread
    endif
endif

# Test Cases
_TEST_CASES=$(patsubst $(TEST_DIR)/%,$(BIN_DIR)/%,$(wildcard $(TEST_DIR)/*.cpp))
TEST_CASES=$(patsubst %.cpp,%.test.o,$(_TEST_CASES))

# Compiler flags
CPPFLAGS = -Wall -g -DDEBUG -I$(LIB_DIR) -I$(SRC_DIR) -std=c++11
GTEST_CPPFLAGS = -Wall -g -I$(LIB_DIR) -I$(SRC_DIR) -Wextra -pthread -std=gnu++0x

# Setting compiler
#CC = g++

# compiler flags for debug
#CPPFLAGS=-std=c++11 -Wall -g -DDEBUG

# compiler flags for release. treat warnings as errors and also optimize code.
# CPPFLAGS=-std=c++11 -Werror=all -O2 

# folder for source code
TEST_DIR = tests
SRC_DIR=src
# folder for header files
LIB_DIR=lib
# folder for generated object files
OBJ_DIR=obj
# folder for BINcutables
BIN_DIR=bin
# name of the binary

all: $(BIN_DIR)/main
#all: main
	-@echo "--- All Built!---"


#$(OBJ_DIR)/%.o: %.cpp %.h $(LIB_DIR)/%.cpp $(LIB_DIR)/%.h $(BIN_DIR)/.dirstamp
#	$(CC) $(CPPFLAGS) -c $< -o $@

# Rules for compiling and running all test cases in 'test folder'

$(OBJ_DIR)/main.o: main.cpp  User.h Movie.h User.cpp Movie.cpp   $(OBJ_DIR)/.dirstamp $(LIB_DIR)/NoSuchElementException.h $(LIB_DIR)/Set.h $(LIB_DIR)/Map.h $(LIB_DIR)/Queue.h $(LIB_DIR)/HashTable.h
	$(CC) -MMD -MP -c $< -o $@ $(CPPFLAGS) -I${LIB_DIR}/

$(OBJ_DIR)/User.o: User.cpp User.h $(LIB_DIR)/Queue.h $(OBJ_DIR)/.dirstamp
	$(CC) -MMD -MP -c $< -o $@ $(CPPFLAGS) -I${LIB_DIR}/

$(OBJ_DIR)/Movie.o: Movie.cpp Movie.h $(LIB_DIR)/Set.h $(OBJ_DIR)/.dirstamp
	$(CC) -MMD -MP -c $< -o $@ $(CPPFLAGS) -I${LIB_DIR}/

$(BIN_DIR)/%.test.o: $(TEST_DIR)/%.cpp $(SRC_DIR)/* $(LIB_DIR)/* $(BIN_DIR)/.dirstamp
	$(CC)  $(GTEST_LL) $(GTEST_CPPFLAGS) -c $< -o $@

$(BIN_DIR)/MergeSortTest: $(TEST_CASES) 
	#$(OBJ_DIR)/main.o $(OBJ_DIR)/User.o $(OBJ_DIR)/Movie.o
	$(CC)   $(GTEST_LL) $^ $(GTEST_CPPFLAGS) -o $@

$(BIN_DIR)/SetTest: $(TEST_CASES) 
	#$(OBJ_DIR)/main.o $(OBJ_DIR)/User.o $(OBJ_DIR)/Movie.o
	$(CC)   $(GTEST_LL) $^ $(GTEST_CPPFLAGS) -o $@

$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR) && touch $@

$(BIN_DIR)/main: $(OBJ_DIR)/main.o $(OBJ_DIR)/User.o $(OBJ_DIR)/Movie.o
	${CC} $^ -o $@ ${CPPFLAGS}

# this rule insures the obj directory exist or it'll create it.
$(OBJ_DIR)/.dirstamp:
	-@mkdir -p $(OBJ_DIR) && touch $@

# Memory check rule. Depends on a fresh binary.
.PHONY: memcheck
memcheck: main ./data/main.txt
	valgrind --tool=memcheck ./$<

.PHONY: tests
tests: $(BIN_DIR)/MergeSortTest
	-@$(BIN_DIR)/MergeSortTest
	-@echo "--- All Tested!---"

# The clean rule
.PHONY: clean
clean:
	-@rm ${OBJ_DIR}/*.o maptest settest *.stackdump *~ $(SRC_DIR)/*~ $(HEADER_DIR)/*~ 2>/dev/null || true


	# First we map every source code to its object file.
# We do this separately for each source file to better identify the header dependency.

#$(OBJ_DIR)/MapTest.o: $(SRC_DIR)/MapTest.cpp $(HEADER_DIR)/Map.h $(OBJ_DIR)/.dirstamp
	#$(CC) -c $< -o $@ $(CPPFLAGS) -I${HEADER_DIR}/
	
#$(OBJ_DIR)/SetTest.o: $(SRC_DIR)/SetTest.cpp $(HEADER_DIR)/Set.h $(OBJ_DIR)/.dirstamp
	#$(CC) -c $< -o $@ $(CPPFLAGS) -I${HEADER_DIR}/

# Now it's time to link both objects. No need for -I argument anymore.
#maptest: $(OBJ_DIR)/MapTest.o $(OBJ_DIR)/Map.o
#maptest: $(OBJ_DIR)/MapTest.o
#	${CC} $^ -o $@ ${CPPFLAGS}
	
#settest: $(OBJ_DIR)/SetTest.o 
#	${CC} $^ -o $@ ${CPPFLAGS}