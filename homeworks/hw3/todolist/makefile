#----------------------------------------#
#              COMMON MACROS             #
#----------------------------------------#

CXX	=g++
CXXF = -Wall -g
BIN_DIR = bin
STD = -std=c++11

#----------------------------------------#
#              MAKE FILE                 #
#----------------------------------------#

all: $(BIN_DIR)/todolist.o todolist-test.cpp
	$(CXX) $(STD) $(CXXF) $(BIN_DIR)/todolist.o todolist-test.cpp -o todolist-test
	-@echo "--- ALL BUILT ---"

#----------------------------------------#
#              OBJECT FILES              #
#----------------------------------------#

$(BIN_DIR)/todolist.o: todolist.h todolist.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c todolist.cpp -o $(BIN_DIR)/todolist.o 

#----------------------------------------#
#                Valgrind                #
#----------------------------------------#

# valgrind: 
#	valgrind --tool=memcheck --leak-check=yes ./search-shell test-small/index.in

#----------------------------------------#
#              BIN CREATION              #
#----------------------------------------#

$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $(BIN_DIR)/.dirstamp

#----------------------------------------#
#             MAKE CLEAN                 #
#----------------------------------------#
clean:
	-@rm -rf $(BIN_DIR) todolist-test todolist-test.dSYM
	-@echo "--- All Clean! ---"
