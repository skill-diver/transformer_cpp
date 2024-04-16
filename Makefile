CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = main.cpp Matrix.cpp MultiHeadAttention.cpp FeedForward.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = transformer

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)