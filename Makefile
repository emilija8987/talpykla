CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall

SRCS = main.cpp pagalbine.cpp studentas.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) vargsiukai.txt kietiakiai.txt

.PHONY: all clean