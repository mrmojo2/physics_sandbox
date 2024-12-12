#include "display.h"

#include <stdexcept>

SDLManager::SDLManager(){
	if(SDL_Init(SDL_INIT_EVERYTHING) !=0 ){
		throw std::runtime_error("Failed to initialize SDL: "+std::string(SDL_GetError()));
	}
}

SDLManager::~SDLManager(){
	SDL_Quit();
}



SDLWindow::SDLWindow(const std::string& title, int width, int height):window(nullptr),renderer(nullptr),is_running(true),window_width(width),window_height(height){
	window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);

	if(!window){
		std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		0		
	);
	if(!renderer){
		SDL_DestroyWindow(window);
		std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
	}

}
