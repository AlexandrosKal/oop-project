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

SRC_OBJS = build/toll.o
TEST_OBJS = build/toll_test.o

BIN_TARGET = build/project.out
TEST_TARGET = build/project_test.out

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include \
            -iquoteinclude/

# Flags passed to the C++ compiler.
#CXXFLAGS += -std=c++03 -Weverything -pedantic -pthread
CXXFLAGS += -std=c++03 -Wall -Wextra -pedantic -pthread

# Build targets.

.PHONY = all clean test
all : $(BIN_TARGET)
clean :
	$(RM) build/*
test : $(TEST_TARGET)
	./styleguide/cpplint/cpplint.py --root=src include/* src/* test/* && \
		./$(TEST_TARGET)

# Builds Google Test and Google Mock.

build/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc -o $@

build/gmock-all.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) -c \
		$(GMOCK_DIR)/src/gmock-all.cc -o $@

build/gmock_main.o : $(GMOCK_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GMOCK_DIR) $(CXXFLAGS) -c \
		$(GMOCK_DIR)/src/gmock_main.cc -o $@

build/gmock_main.a : build/gmock-all.o build/gtest-all.o build/gmock_main.o
	$(AR) $(ARFLAGS) $@ $^

# Project builds.

build/project.o : src/project.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/toll.o : src/toll.cc include/toll.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/toll_test.o : test/toll_test.cc include/toll.h $(GMOCK_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_TARGET) : $(SRC_OBJS) build/project.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
$(TEST_TARGET) : $(SRC_OBJS) $(TEST_OBJS) build/gmock_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
