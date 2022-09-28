export module Application;
import Events;
import Platform;
import Graphics;
import stdlib;

export class Application
{
private:
	static Application* Instance;

private:
	bool ShouldRun = true;
	PLTF::Window* Window;
	GFX::RenderPass renderPass;
	GFX::Surface surface;
	GFX::Swapchain swapchain;
	GFX::Image images[3];
	GFX::ImageView views[3];
	GFX::Framebuffer framebuffers[2];
	GFX::Queue presentQueue;
	GFX::Image depthBuffer;
	GFX::Queue renderQueue; uint32_t renderQueueIndex;
	GFX::Buffer stagingBuffer;
	GFX::Buffer vertexBuffer;
	GFX::Buffer indexBuffer;
	GFX::CmdPool renderPool;
	GFX::CmdList cmdList;
	GFX::Shader shaders[2];
	GFX::DescriptorLayout descriptorLayout;
	GFX::PipelineLayout layout;
	GFX::Pipeline pipeline;
	GFX::Semaphore timelineSemaphore;
	GFX::Semaphore binarySemaphore;
	uint64_t semaphoreValue = 1;

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