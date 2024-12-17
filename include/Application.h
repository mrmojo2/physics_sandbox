#ifndef APPLICATION_H
#define APPLICATION

#include "Particle.h"

#include <vector>

class Application{
private:
	bool running = false;
	std::vector<Particle*> particles;
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
