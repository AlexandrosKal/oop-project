# Google Test configuration.

GTEST_DIR = googletest/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# Project configuration.

SRC_OBJS = build/car.o \
           build/junction.o \
           build/segment.o \
           build/toll.o
TEST_OBJS = build/car_test.o \
            build/junction_test.o \
            build/segment_test.o \
            build/toll_test.o

BIN_TARGET = build/project.out
TEST_TARGET = build/project_test.out

# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include -iquote include

# Flags passed to the C++ compiler.
#CXXFLAGS += -std=c++03 -Weverything -pedantic -pthread
CXXFLAGS += -std=c++03 -Wall -Wextra -pedantic -pthread

# Build targets.

.PHONY = all clean test
all : $(BIN_TARGET)
clean :
	$(RM) build/*
test : $(TEST_TARGET)
	./styleguide/cpplint/cpplint.py include/* src/* test/* && ./$(TEST_TARGET)

# Builds Google Test.

build/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc -o $@

build/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest_main.cc -o $@

build/gtest_main.a : build/gtest-all.o build/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Project builds.

build/project.o : src/project.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/car.o : src/car.cc include/car.h include/segment.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/car_test.o : test/car_test.cc include/car.h include/segment.h \
                   $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/junction.o : src/junction.cc include/junction.h include/car.h \
                   include/toll.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/junction_test.o : test/junction_test.cc include/junction.h \
                        include/car.h include/toll.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/segment.o : src/segment.cc include/segment.h include/car.h \
                  include/junction.h include/toll.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/segment_test.o : test/segment_test.cc include/segment.h include/car.h \
                       include/junction.h include/toll.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/toll.o : src/toll.cc include/toll.h include/car.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/toll_test.o : test/toll_test.cc include/toll.h include/car.h \
                    $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_TARGET) : $(SRC_OBJS) build/project.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
$(TEST_TARGET) : $(SRC_OBJS) $(TEST_OBJS) build/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
