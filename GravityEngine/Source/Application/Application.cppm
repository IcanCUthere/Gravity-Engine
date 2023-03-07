export module Application;
import Events;
import Platform;
import Graphics;
import Viewport;
import Timestep;
import Camera;
import stdlib;

const uint32_t MAX_IMAGE_COUNT = 3;


export class Application
{
private:
	static Application* Instance;

private:
	bool ShouldRun = true;
	GFX::RenderPass renderPass;
	GFX::Queue renderQueue;
	GFX::Buffer stagingBuffer;
	GFX::Buffer vertexBuffer;
	GFX::Buffer indexBuffer;
	GFX::Buffer uniformBuffer;
	GFX::Image image;
	GFX::ImageView imageView;
	GFX::Sampler sampler;
	GFX::Shader shaders[2];
	GFX::DescriptorLayout descriptorLayout;
	GFX::DescriptorPool descriptorPool;
	GFX::DescriptorSet descriptorSet;
	GFX::PipelineLayout layout;
	GFX::Pipeline pipeline;
	GFX::Semaphore timelineSemaphore;
	GFX::Semaphore binarySemaphores[MAX_IMAGE_COUNT];
	GFX::CmdPool cmdPools[MAX_IMAGE_COUNT];
	GFX::CmdList cmdLists[MAX_IMAGE_COUNT];
	uint64_t semaphoreValue = 1;

	Viewport<MAX_IMAGE_COUNT>* viewport;
	Camera camera;

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