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

	particle = new Particle(50,25,5);
	particle->acceleration = Vec2(0.0,9.8*PIXELS_PER_METER);
	particle->velocity = Vec2(200,0);
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
	if(delay>0){				//delay can be negative if a frame loop take more time than MILLISECONDS_PER_FRAME
		SDL_Delay(delay);
	}
	
	//delta time: difference between the current frame and the last frame in seconds
	//used to implement fps independant movement
	float deltaTime = (SDL_GetTicks() - previousFrameTime)/1000.0f;
	if(deltaTime > MILLISECONDS_PER_FRAME/1000.0f){
		deltaTime = MILLISECONDS_PER_FRAME/1000.0f;
	}	

	//set time of this frame to be used in the next frame
	previousFrameTime = SDL_GetTicks();	

	particle->velocity += particle->acceleration * deltaTime;
	particle->position += particle->velocity * deltaTime;

	
	if((particle->position.y > (Graphics::windowHeight - Particle::radius))){
		particle->position.y = Graphics::windowHeight - Particle::radius;	//putting particle on the edges if it exceds
		particle->velocity.y *= -0.9;						//making the collision not perfectly elastic
	}else if(particle->position.y < (0 + Particle::radius)){
		particle->position.y = Particle::radius;
		particle->velocity.y *= -0.9;
	}
	if(particle->position.x > (Graphics::windowWidth - Particle::radius)){
		particle->position.x = Graphics::windowWidth - Particle::radius;	//putting particle on the edges if it exceds
		particle->velocity.x *= -0.9;						//making the collision not perfectly elastic
	}else if(particle->position.x < (0 + Particle::radius)){
		particle->position.x = Particle::radius;
		particle->velocity.x *= -0.9;
	}	
}
void Application::render(){
	Graphics::ClearScreen(0xFF056263);
	Graphics::DrawFillCircle(particle->position.x,particle->position.y,Particle::radius,0xffffffff);
	Graphics::RenderFrame();	
}
void Application::destroy(){
	delete particle;
	Graphics::CloseWindow();
}
