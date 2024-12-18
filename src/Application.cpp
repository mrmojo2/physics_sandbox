#include "Application.h"
#include "Graphics.h"
#include "Constants.h"
#include "Force.h"

#include <iostream>
#include <stdint.h>

bool Application::isRunning(){
	return running;
}

void Application::setup(){
	running = Graphics::OpenWindow();

	fluid.x = 0;
	fluid.y = Graphics::windowHeight/2;
	fluid.w = Graphics::windowWidth;
	fluid.h = Graphics::windowHeight/2;

	Particle* particle1 = new Particle(50,25,5);
	//Particle* particle2 = new Particle(200,25,20);

	particles.push_back(particle1);
	//particles.push_back(particle2);

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
				if(event.key.keysym.sym == SDLK_UP)
					pushForce.y = -100*PIXELS_PER_METER;
				if(event.key.keysym.sym == SDLK_DOWN)
					pushForce.y = 100*PIXELS_PER_METER;
				if(event.key.keysym.sym == SDLK_LEFT)
					pushForce.x = -100*PIXELS_PER_METER;
				if(event.key.keysym.sym == SDLK_RIGHT)
					pushForce.x = +100*PIXELS_PER_METER;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_UP)
					pushForce.y = 0;
				if(event.key.keysym.sym == SDLK_DOWN)
					pushForce.y = 0;
				if(event.key.keysym.sym == SDLK_LEFT)
					pushForce.x = 0;
				if(event.key.keysym.sym == SDLK_RIGHT)
					pushForce.x = 0;
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

	
	//apply forces to the particles
	for(auto particle:particles){
		//weight force
		particle->addForce(Vec2(0.0,9.8*PIXELS_PER_METER*particle->mass));
		//wind force
		particle->addForce(Vec2(100,0.0));
		//pushForce from keyboard
		particle->addForce(pushForce);
		//drag force from fluid
		if(particle->position.y > fluid.y){
			Vec2 dragForce = Force::getDragForce(*particle , 0.0075);
			particle->addForce(dragForce);
		}
	}
	
	//perform integration
	for(auto particle: particles){
		particle->integrate(deltaTime);
	}	

	//window boundary
	for(auto particle:particles){
		if((particle->position.y > (Graphics::windowHeight - particle->radius))){
			particle->position.y = Graphics::windowHeight - particle->radius;	//putting particle on the edges if it exceds
			particle->velocity.y *= -0.9;						//making the collision not perfectly elastic
		}else if(particle->position.y < (0 + particle->radius)){
			particle->position.y = particle->radius;
			particle->velocity.y *= -0.9;
		}
		if(particle->position.x > (Graphics::windowWidth - particle->radius)){
			particle->position.x = Graphics::windowWidth - particle->radius;	//putting particle on the edges if it exceds
			particle->velocity.x *= -0.9;						//making the collision not perfectly elastic
		}else if(particle->position.x < (0 + particle->radius)){
			particle->position.x = particle->radius;
			particle->velocity.x *= -0.9;
		}	
	}
}
void Application::render(){
	Graphics::ClearScreen(0xFFa9afb0);

	//render the fluid
	Graphics::DrawFillRect(fluid.x + fluid.w/2,fluid.y + fluid.h/2 , fluid.w, fluid.h, 0xffb86914);

	//render the particcles
	for(auto particle:particles)
		Graphics::DrawFillCircle(particle->position.x,particle->position.y,particle->radius,0xffffffff);
	
	Graphics::RenderFrame();	
}
void Application::destroy(){
	for(auto particle:particles){
		delete particle;
	}
	Graphics::CloseWindow();
}
