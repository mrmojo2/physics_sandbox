#include <iostream>

#include "Physics/Vector.h"
#include "Application.h"

int main(){
	std::cout<<"hello simulated world"<<std::endl;
	
	Application app;

	app.setup();
	while(app.isRunning()){
		app.input();
		app.update();
		app.render();
	}
	app.destroy();

	return 0;
}
