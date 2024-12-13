#ifndef APPLICATION_H
#define APPLICATION


class Application{
private:
	bool running = false;
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
