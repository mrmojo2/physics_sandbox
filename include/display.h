#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>

class SDLManager{
public:
	SDLManager();
	~SDLManager();
};

class SDLWindow{
private:
	SDL_Window*    window;
	SDL_Renderer*  renderer;
	bool is_running;
	int window_width;
	int window_height;
public:
	SDLWindow(const std::string& title, int width, int height);
	~SDLWindow();

	void setup();
	void process_input();
	void update();
	void render();
};

#endif
