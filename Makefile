all:
	gcc -c cocoa-main.m
	g++ -o gl2d -framework SDL -framework SDL_image -framework Cocoa -framework OpenGL -I/Library/Frameworks/SDL.framework/Headers *.cpp *.o