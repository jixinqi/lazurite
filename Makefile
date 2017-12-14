CXX                            = g++ -std=c++11
CXXFLAGS                       = -Wall -Werror
LDFLAGS                        = -lboost_system

SRC_DIR                        = ./src:./src/lazurite_core
BUILD_DIR                      = ./tmp
BIN_DIR                        = ./bin

vpath %.cpp                    $(SRC_DIR)
.PHONY                         : clean

default                        : $(BIN_DIR)/lazurite

$(BIN_DIR)/lazurite            : $(BUILD_DIR)/main.o \
                                 $(BUILD_DIR)/http_listen.o \
                                 $(BUILD_DIR)/http_server.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o               : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean :
	-rm -rf $(BUILD_DIR)/*
	-rm -rf $(BIN_DIR)/*
