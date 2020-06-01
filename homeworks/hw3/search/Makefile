#----------------------------------------#
#              COMMON MACROS             #
#----------------------------------------#
CXX	=g++
CXXF = -Wall -g
BIN_DIR = bin
STD = -std=c++11
GTEST_LL = -I /usr/include/gtest -l gtest -l gtest_main -pthread

#----------------------------------------#
#            OBJECT MACROS               #
#----------------------------------------#
# Total Macro #
OBJ = pageparser.h $(BIN_DIR)/md_parser.o $(BIN_DIR)/txt_parser.o $(BIN_DIR)/webpage.o $(BIN_DIR)/util.o $(BIN_DIR)/combiners.o $(BIN_DIR)/searcheng.o $(BIN_DIR)/searchui.o $(BIN_DIR)/handler.o $(BIN_DIR)/cmdhandler.o

# Search Macro #
OBJ_Search = pageparser.h $(BIN_DIR)/util.o $(BIN_DIR)/webpage.o $(BIN_DIR)/md_parser.o $(BIN_DIR)/txt_parser.o $(BIN_DIR)/combiners.o $(BIN_DIR)/searcheng.o

# Parse Macro #
OBJ_Parse = $(BIN_DIR)/util.o $(BIN_DIR)/webpage.o $(BIN_DIR)/md_parser.o

#----------------------------------------#
#              MAKE FILE                 #
#----------------------------------------#

all: $(OBJ) search-shell.cpp
	$(CXX) $(STD) $(CXXF) $(OBJ) search-shell.cpp -o search-shell
	-@echo "--- All Built ---"

#----------------------------------------#
#              TEST CASES                #
#----------------------------------------#
# Handler Test #
$(BIN_DIR)/handler_test: $(OBJ) handler_test.cpp
	$(CXX) $(CXXF) $(OBJ) handler_test.cpp -o $(BIN_DIR)/handler_test

# Search Engine Test #
$(BIN_DIR)/searcheng_test: $(OBJ_Search) searcheng_test.cpp
	$(CXX) $(CXXF) $(OBJ_Search) searcheng_test.cpp -o $(BIN_DIR)/searcheng_test

# MD Parser Test #
$(BIN_DIR)/md_parser_test: $(OBJ_Parse) md_parser_test.cpp
	$(CXX) $(CXXF) $(OBJ_Parse) md_parser_test.cpp -o $(BIN_DIR)/md_parser_test

#----------------------------------------#
#              OBJECT FILES              #
#----------------------------------------#
# Search Ui #
$(BIN_DIR)/searchui.o: searchui.h searchui.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c searchui.cpp -o $(BIN_DIR)/searchui.o

# Search Eng #
$(BIN_DIR)/searcheng.o: searcheng.h  searcheng.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c searcheng.cpp -o $(BIN_DIR)/searcheng.o

# Handler #
$(BIN_DIR)/handler.o: handler.h handler.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c handler.cpp -o $(BIN_DIR)/handler.o

# CMDHandler #
$(BIN_DIR)/cmdhandler.o: cmdhandler.h cmdhandler.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c cmdhandler.cpp -o $(BIN_DIR)/cmdhandler.o

# Combiners #
$(BIN_DIR)/combiners.o: combiners.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c combiners.cpp -o $(BIN_DIR)/combiners.o

# WebPage #
$(BIN_DIR)/webpage.o: webpage.h webpage.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c webpage.cpp -o $(BIN_DIR)/webpage.o

# TXT Parser #
$(BIN_DIR)/txt_parser.o: txt_parser.h txt_parser.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c txt_parser.cpp -o $(BIN_DIR)/txt_parser.o

# MD Parser #
$(BIN_DIR)/md_parser.o: md_parser.h md_parser.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c md_parser.cpp -o $(BIN_DIR)/md_parser.o

# Util #
$(BIN_DIR)/util.o: util.h util.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXF) -c util.cpp -o $(BIN_DIR)/util.o


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
.PHONY: clean tests

tests: $(BIN_DIR)/search_test
	-@$(BIN_DIR)/search_test
	-@echo "--- All Tested! ---"

clean:
	-@rm -rf $(BIN_DIR) search-shell
	-@echo "--- All Clean! ---"

	