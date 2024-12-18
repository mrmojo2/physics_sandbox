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

	
		//planetary motion type shit
	/*Particle* particle_small = new Particle(100,200,1);
	Particle* particle_big = new Particle(500,500,20);

	particles.push_back(particle_small);
	particles.push_back(particle_big);*/

	
		//compoud pendulum...kindof
	/*Spring* spring1= new Spring(Vec2(500,200), 200, 1500);
	Particle* bob1 = new Particle(spring1->anchor.x,spring1->anchor.y+spring1->eqb_length,5);
	particles.push_back(bob1);
	springMassSystems.push_back(SpringMass(spring1,bob1));

	Spring* spring2= new Spring(bob1->position, 200, 6000);
	Particle* bob2 = new Particle(spring2->anchor.x, spring2->anchor.y+spring2->eqb_length,5);
	particles.push_back(bob2);
	springMassSystems.push_back(SpringMass(spring2,bob2));*/

	for(int i=1;i<=3;i++){
		Particle* p = new Particle(Graphics::windowWidth/2,100 + (i*60),2);
		Spring*   s = new Spring(Vec2(Graphics::windowWidth/2,100+(i-1)*60),60,5000);
		springMassSystems.push_back(SpringMass(s,p));
		particles.push_back(p);
	}	


}

void Application::input(){
	static int buttonDownTime, buttonUpTime;
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
			case SDL_MOUSEMOTION:
				mousePos.x = event.motion.x;
				mousePos.y = event.motion.y;
				break;

			case SDL_MOUSEBUTTONDOWN:{
				int curMouseX = event.motion.x;
				int curMouseY = event.motion.y;		
				if(event.button.button == SDL_BUTTON_LEFT){
					for(int i=0;i<particles.size();i++){
						if( (curMouseX > particles[i]->position.x - (particles[i]->radius+5)) && (curMouseX < particles[i]->position.x + (particles[i]->radius+5)) && 
						    (curMouseY > particles[i]->position.y - (particles[i]->radius+5)) && (curMouseY < particles[i]->position.y + (particles[i]->radius+5)) ){
							drawMouseImpulseLine = true;
							mouseImpulseParticleIndex = i;
						}
					}
					buttonDownTime = SDL_GetTicks();
				}
				break;
			}
			
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT){
					buttonUpTime = SDL_GetTicks();
					if(drawMouseImpulseLine){
						drawMouseImpulseLine = false;
						Vec2 impulseDir = (particles[mouseImpulseParticleIndex]->position - mousePos).unit();
						float impulseMag = (particles[mouseImpulseParticleIndex]->position - mousePos).magnitude();
						particles[mouseImpulseParticleIndex]->velocity = impulseDir*impulseMag;
					}else{
						//Particle* p = new Particle(event.motion.x, event.motion.y, (buttonUpTime-buttonDownTime)/50);
						//particles.push_back(p);
					}
				}
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
		
		//pushForce from keyboard
		particle->addForce(pushForce);
		
		//drag force
		Vec2 drag = Force::getDragForce(*particle, 0.0002);
		//particle->addForce(drag);

	}

	//apply spring force to spring bobs
	Vec2 springForce = Force::getSpringForce(springMassSystems[0]);
	springMassSystems[0].bob->addForce(springForce);
	for(int i=1;i<springMassSystems.size();i++){
		Particle* currentBob = springMassSystems[i].bob;
		Particle* previousBob = springMassSystems[i-1].bob;
		
		Vec2 springForce = Force::getSpringForce(springMassSystems[i]);
		currentBob->addForce(springForce);
		previousBob->addForce(-springForce);

	}

	
	
	//springMassSystems[1].sp->anchor = springMassSystems[0].bob->position;

	
	//apply gravitational force to the first two particles
	/*Vec2 gravitationalForce = Force::getGravitationalForce(*particles[0],*particles[1],1000,5,100);
	particles[0]->addForce(-gravitationalForce);
	particles[1]->addForce(gravitationalForce);*/

	
	//perform integration
	for(auto particle: particles){
		particle->integrate(deltaTime);
	}

	for(int i=1; i<springMassSystems.size();i++){
		springMassSystems[i].sp->anchor = springMassSystems[i-1].bob->position;
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
	Graphics::ClearScreen(0xFF112233);

	//render the fluid
	//Graphics::DrawFillRect(fluid.x + fluid.w/2,fluid.y + fluid.h/2 , fluid.w, fluid.h, 0xffb86914);
	

	if(drawMouseImpulseLine){
		Graphics::DrawLine(particles[mouseImpulseParticleIndex]->position.x, particles[mouseImpulseParticleIndex]->position.y, mousePos.x, mousePos.y, 0xff0000ff);
	}

	//render springs
	for(auto sm:springMassSystems){
		Graphics::DrawFillCircle(sm.sp->anchor.x, sm.sp->anchor.y,2,0xff0011e3);
		Graphics::DrawLine(sm.sp->anchor.x, sm.sp->anchor.y,sm.bob->position.x, sm.bob->position.y,0xffffffff);
	}	
	//render the particcles
	for(auto particle:particles)
		Graphics::DrawFillCircle(particle->position.x,particle->position.y,particle->radius,0xffffffff);
	
	Graphics::RenderFrame();	
}
void Application::destroy(){
	for(auto particle:particles){
		delete particle;
	}
	for(auto sm:springMassSystems){
		delete sm.sp;
	}
	Graphics::CloseWindow();
}
