CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

LDFLAGS = -lm

SRCS = histograma.cpp BmpLib2.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = bin/histograma

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) saida_*.bmp

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
