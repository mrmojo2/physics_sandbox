#ifndef APPLICATION_H
#define APPLICATION

#include "Particle.h"

class Application{
private:
	bool running = false;
	Particle *particle;
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
