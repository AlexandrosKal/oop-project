# OS X
#CXXFLAGS = -Weverything -pedantic-errors -std=c++98

# GNU/Linux
CXXFLAGS = -Wall -Wextra -pedantic-errors -std=c++98

OBJS = project.o
TARGET = project.out

.PHONY = all clean
all: $(TARGET)
clean:
	$(RM) $(OBJS) $(TARGET)

project.o: project.cc

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@
