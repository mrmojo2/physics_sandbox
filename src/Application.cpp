#include "Application.h"
#include "Graphics.h"

bool Application::isRunning(){
	return running;
}

void Application::setup(){
	running = Graphics::OpenWindow();
}

void Application::input(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					running = false;
				break;
		}
	}
}
void Application::update(){
	
}
void Application::render(){
	Graphics::ClearScreen(0xFF056263);
	Graphics::DrawFillCircle(200,200,40,0xffffffff);
	Graphics::RenderFrame();	
}
void Application::destroy(){
	Graphics::CloseWindow();
}
