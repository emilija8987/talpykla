CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall

SRCS = main.cpp pagalbine.cpp studentas.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)