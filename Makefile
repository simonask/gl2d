all:
	gcc -g -c cocoa-main.m
	g++ -g -O3 -msse2 -march=nocona -o gl2d -framework SDL -framework SDL_image -framework Cocoa -framework OpenGL -I/Library/Frameworks/SDL.framework/Headers *.cpp *.o