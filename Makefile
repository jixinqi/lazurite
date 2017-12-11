CXX                            = g++ -std=c++11
CXXFLAGS                       = -Wall -Werror
LDFLAGS                        = -lboost_system

SRC_DIR                        = ./src
BUILD_DIR                      = ./tmp
BIN_DIR                        = ./bin

vpath %.cpp                    $(SRC_DIR)

default : $(BIN_DIR)/lazurite

$(BIN_DIR)/lazurite : $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean :
	-rm -rf $(BUILD_DIR)/*
	-rm -rf $(BIN_DIR)/*
