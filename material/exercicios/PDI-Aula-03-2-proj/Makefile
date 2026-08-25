CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
INCLUDES = -Iinclude

LDFLAGS = -lGL -lGLU -lglut -lm

SRCS = ImageTest.cpp ImageClass.cpp BmpLib2.cpp src/PDI.cpp
OBJS = ImageTest.o ImageClass.o BmpLib2.o src/PDI.o
TARGET = bin/PDI-Aula

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	cd bin && ./PDI-Aula

.PHONY: all clean run
