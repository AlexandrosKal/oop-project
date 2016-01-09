# Google Test configuration.

GTEST_DIR = googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# Project configuration.

BUILD_DIR = build

SRC_DIR = src
SRC_OBJS = $(BUILD_DIR)/project.o

TEST_DIR = test
TEST_OBJS = $(BUILD_DIR)/project_test.o

BIN_TARGET = $(BUILD_DIR)/project.out
TEST_TARGET = $(BUILD_DIR)/project_test.out

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
#CXXFLAGS += -std=c++03 -Weverything -pedantic -pthread
CXXFLAGS += -std=c++03 -Wall -Wextra -pedantic -pthread

# Build targets.

.PHONY = all clean test
all : $(BIN_TARGET)
clean :
	$(RM) $(BUILD_DIR)/*
test : $(TEST_TARGET)
	./$(TEST_TARGET)

# Builds gtest.a and gtest_main.a.

$(BUILD_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc -o $@
$(BUILD_DIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest_main.cc -o $@
$(BUILD_DIR)/gtest_main.a : $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Project builds.

$(BUILD_DIR)/project.o : $(SRC_DIR)/project.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
$(BUILD_DIR)/project_test.o : $(TEST_DIR)/project_test.cc $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_TARGET) : $(SRC_OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
$(TEST_TARGET) : $(SRC_OBJS) $(TEST_OBJS) $(BUILD_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
