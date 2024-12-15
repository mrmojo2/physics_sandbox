#include "Application.h"
#include "Graphics.h"
#include "Constants.h"

#include <iostream>
#include <stdint.h>

bool Application::isRunning(){
	return running;
}

void Application::setup(){
	running = Graphics::OpenWindow();

	particle = new Particle(0,0,5);
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
	//maintain constant fps
	static int  previousFrameTime;
	int delay = MILLISECONDS_PER_FRAME - (SDL_GetTicks()-previousFrameTime);
	if(delay>0){				//for the first iteration since previousFrameTime = 0 the delay will be negative!
		SDL_Delay(delay);
	}
	
	previousFrameTime = SDL_GetTicks();	

	particle->velocity = Vec2(5,5);
	particle->position += particle->velocity;	
}
void Application::render(){
	Graphics::ClearScreen(0xFF056263);
	Graphics::DrawFillCircle(particle->position.x,particle->position.y,4,0xffffffff);
	Graphics::RenderFrame();	
}
void Application::destroy(){
	delete particle;
	Graphics::CloseWindow();
}