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
	
	Body* b1 = new Body(Circle(100),500,200,2);
	bodies.push_back(b1);
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

			/*case SDL_MOUSEBUTTONDOWN:{
				int curMouseX = event.motion.x;
				int curMouseY = event.motion.y;		
				if(event.button.button == SDL_BUTTON_LEFT){
					for(int i=0;i<bodies.size();i++){
						if( (curMouseX > bodies[i]->position.x - (bodies[i]->radius+5)) && (curMouseX < bodies[i]->position.x + (bodies[i]->radius+5)) && 
						    (curMouseY > bodies[i]->position.y - (bodies[i]->radius+5)) && (curMouseY < bodies[i]->position.y + (bodies[i]->radius+5)) ){
							drawMouseImpulseLine = true;
							mouseImpulseBodyIndex = i;
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
						Vec2 impulseDir = (bodies[mouseImpulseBodyIndex]->position - mousePos).unit();
						float impulseMag = (bodies[mouseImpulseBodyIndex]->position - mousePos).magnitude();
						bodies[mouseImpulseBodyIndex]->velocity = impulseDir*impulseMag;
					}else{
						//Body* p = new Body(event.motion.x, event.motion.y, (buttonUpTime-buttonDownTime)/50);
						//bodies.push_back(p);
					}
				}
				break;*/
				


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

	
	//apply forces to the bodies
	for(auto body:bodies){
		//weight force
		body->addForce(Vec2(0.0,9.8*PIXELS_PER_METER*body->mass));
		
		//pushForce from keyboard
		body->addForce(pushForce);
		
		//drag force
		Vec2 drag = Force::getDragForce(*body, 0.002);
		//body->addForce(drag);
		
		//apply torque
		body->addTorque(200);
	}


	//perform integration
	for(auto body: bodies){
		body->integrateLinear(deltaTime);
		body->integrateAngular(deltaTime);
	}


	//window boundary
	for(auto body:bodies){
		if(body->shape->getShapeType() == CIRCLE){
			Circle* c = (Circle* ) body->shape;
			if((body->position.y > (Graphics::windowHeight - c->radius))){
				body->position.y = Graphics::windowHeight - c->radius;	//putting body on the edges if it exceds
				body->velocity.y *= -0.9;						//making the collision not perfectly elastic
			}else if(body->position.y < (0 + c->radius)){
				body->position.y = c->radius;
				body->velocity.y *= -0.9;
			}
			if(body->position.x > (Graphics::windowWidth - c->radius)){
				body->position.x = Graphics::windowWidth - c->radius;	//putting body on the edges if it exceds
				body->velocity.x *= -0.9;						//making the collision not perfectly elastic
			}else if(body->position.x < (0 + c->radius)){
				body->position.x = c->radius;
				body->velocity.x *= -0.9;
			}	
		}
	}
}
void Application::render(){
	Graphics::ClearScreen(0xFF112233);
	

	if(drawMouseImpulseLine){
		Graphics::DrawLine(bodies[mouseImpulseBodyIndex]->position.x, bodies[mouseImpulseBodyIndex]->position.y, mousePos.x, mousePos.y, 0xff0000ff);
	}

	//render springs
	for(auto sm:springMassSystems){
		Graphics::DrawFillCircle(sm.sp->anchor->x, sm.sp->anchor->y,2,0xff0011e3);
		Graphics::DrawLine(sm.sp->anchor->x, sm.sp->anchor->y,sm.bob->position.x, sm.bob->position.y,0xffffffff);
	}	
	//render the particcles
	for(auto body:bodies)
		if(body->shape->getShapeType() == CIRCLE){
			Circle* c = (Circle* )body->shape;
			Graphics::DrawCircle(body->position.x,body->position.y,c->radius,body->angle,0xffffffff);
		}
	Graphics::RenderFrame();	
}
void Application::destroy(){
	for(auto body:bodies){
		delete body;
	}
	for(auto sm:springMassSystems){
		delete sm.sp;
	}
	Graphics::CloseWindow();
}
