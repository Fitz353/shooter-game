CXX = g++
CXXFLAGS = -Wall -std=c++20 -IC:/msys64/ucrt64/include
LDFLAGS = -LC:/msys64/ucrt64/lib -lSDL3 -mwindows -mconsole
SRCS = main.cpp game.cpp player.cpp bullet.cpp
TARGET = main.exe

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	del $(TARGET)

.PHONY: run clean
