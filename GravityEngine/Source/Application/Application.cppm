export module Application;
import Events;
import Platform;
import stdlib;

export class Application
{
private:
	static Application* Instance;

private:
	bool ShouldRun = true;
	PLTF::Window* Window;
	//ACamera Camera; skrrrrt skrrrt

	Application(const char* name);
	Application(const Application&) = delete;
	Application(Application&&) =  delete; 
	~Application();
	void operator=(const Application&) = delete;
	void operator=(Application&&) = delete;

	void OnEvent(EVNT::Event& e);
	bool OnWindowResize(EVNT::WindowResizeEvent& e);
	bool OnWindowClose(EVNT::WindowCloseEvent& e);

public:
	static Application& Initialize(const char* name);
	static void Terminate();
	static Application& Get() { return *Instance; }

	void Run();
};

Application* Application::Instance = nullptr;