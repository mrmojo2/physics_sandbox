#ifndef APPLICATION_H
#define APPLICATION

#include "Particle.h"
#include "Vector.h"

#include <vector>
#include <SDL2/SDL.h>

class Application{
private:
	bool running = false;
	std::vector<Particle*> particles;
	Vec2 pushForce = Vec2(0,0);
	SDL_Rect fluid;
public:
	Application() = default;
	~Application() = default;

	bool isRunning();
	void setup();
	void input();
	void update();
	void render();
	void destroy();
};


#endif
