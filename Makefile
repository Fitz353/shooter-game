main:
	g++ main.cpp -o main.exe $(shell pkg-config --cflags --libs sdl3) -mconsole
	./main.exe
