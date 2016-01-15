# Google Test and Google Mock configuration.

GTEST_DIR = googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

GMOCK_DIR = googletest/googlemock
GMOCK_HEADERS = $(GMOCK_DIR)/include/gmock/*.h \
                $(GMOCK_DIR)/include/gmock/internal/*.h \
                $(GTEST_HEADERS)
GMOCK_SRCS_ = $(GMOCK_DIR)/src/*.cc $(GMOCK_HEADERS)

# Project configuration.

BUILD_DIR = build

SRC_DIR = src
SRC_OBJS =

TEST_DIR = test
TEST_OBJS = $(BUILD_DIR)/project_test.o

BIN_TARGET = $(BUILD_DIR)/project.out
TEST_TARGET = $(BUILD_DIR)/project_test.out

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include

# Flags passed to the C++ compiler.
#CXXFLAGS += -std=c++03 -Weverything -pedantic -pthread
CXXFLAGS += -std=c++03 -Wall -Wextra -pedantic -pthread

# Build targets.

.PHONY = all clean test
all : $(BIN_TARGET)
clean :
	$(RM) $(BUILD_DIR)/*
test : $(TEST_TARGET)
	./styleguide/cpplint/cpplint.py --root=src src/* test/* && ./$(TEST_TARGET)

# Builds Google Test and Google Mock.

$(BUILD_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc -o $@

$(BUILD_DIR)/gmock-all.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) -c \
		$(GMOCK_DIR)/src/gmock-all.cc -o $@

$(BUILD_DIR)/gmock_main.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) -c \
		$(GMOCK_DIR)/src/gmock_main.cc -o $@

$(BUILD_DIR)/gmock_main.a : $(BUILD_DIR)/gmock-all.o \
                            $(BUILD_DIR)/gtest-all.o \
                            $(BUILD_DIR)/gmock_main.o
	$(AR) $(ARFLAGS) $@ $^

# Project builds.

$(BUILD_DIR)/project.o : $(SRC_DIR)/project.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/project_test.o : $(TEST_DIR)/project_test.cc $(GMOCK_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_TARGET) : $(SRC_OBJS) $(BUILD_DIR)/project.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
$(TEST_TARGET) : $(SRC_OBJS) $(TEST_OBJS) $(BUILD_DIR)/gmock_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
