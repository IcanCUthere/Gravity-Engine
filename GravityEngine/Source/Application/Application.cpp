module;
#include "Core/DebugUtils.h"

//#define GLM_FORCE_RADIANS
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

module Application;
import Graphics;

const uint32_t resX = 1000, resY = 1000;

float positions[20] = {
	-0.5f, -0.5f, 0.f, 1.f, 0.f,
	 0.5f,  0.5f, 0.f, 0.f, 1.f,
	-0.5f,  0.5f, 0.f, 1.f, 1.f,
	 0.5f, -0.5f, 0.f, 0.f, 0.f
};

uint32_t indices[6] = {
	2, 1, 0,
	0, 1, 3
};

Application::Application(const char* name)
//	: Camera(AVector3(2.f, 2.f, 2.f), AVector3(0.f, 0.f, 0.f), resX / resY, 45.f)
{
//	int texWidth, texHeight, texChannels;
//	STBI::stbi_uc* pixels = STBI::stbi_load("Resources\\texture.jpg", &texWidth, &texHeight, &texChannels, STBI::STBI_rgb_alpha);
//
	GFX::Initialize(GFX::EAPI::Vulkan);
//
//	GFX::HSampler sampler;
//	GFX::CreateSampler(&sampler, GFX::ESampleFilter::Linear, GFX::ESampleAddressMode::Repeat);
//
	Window = PLTF::CreateWindow(resX, resY, name);
	Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
//
//	GFX::UVertexInputInfo vertexInput = { 0, false, { GFX::EFormat::R32G32B32_SF, GFX::EFormat::R32G32_SF } };
//	vertexArray = new AVertexArray(sizeof(positions), sizeof(indices), vertexInput);
//	uniformBuffer = new AUniformBuffer(sizeof(glm::mat4));
//	texture = new ATexture(GFX::USize3D{ (uint32_t)texWidth, (uint32_t)texHeight, 1 }, GFX::EFormat::R8G8B8A8_SRGB);
//
//	viewport = GFX::CreateViewport(Window->GetNativeWindow(), resX, resY);
//	shader = GFX::CreateShader("Resources\\Shader2.glsl");
//	graphicsPool = GFX::CreateCmdListPool(GFX::ECmdListUsage::Graphics, 1, 0);
//	transferPool = GFX::CreateCmdListPool(GFX::ECmdListUsage::Transfer, 1, 0);
//
//	GFX::ICmdList* list = graphicsPool->GetList(0);
//	list->BeginRecording(GFX::ERenderStage::Transfer);

	//GFX::UImageBarrier barrier1{ GFX::EAccessFlags::None, GFX::EAccessFlags::TransferWrite, texture,  GFX::EImageLayout::TransferDestinationOptimal };
	//GFX::UImageBarrier barrier2{ GFX::EAccessFlags::TransferWrite, GFX::EAccessFlags::ShaderRead, texture,  GFX::EImageLayout::ShaderReadOnlyOptimal };

	//GFX::InsertPipelineBarriers(list, GFX::EPipelineStage::TopOfPipe, GFX::EPipelineStage::Transfer, {}, {}, { barrier1 });
	//texture->UpdateTextureData(pixels, texWidth * texHeight * 4, list);
	//GFX::InsertPipelineBarriers(list, GFX::EPipelineStage::Transfer, GFX::EPipelineStage::FragmentShader, {}, {}, { barrier2 } );

	//vertexArray->UpdateData(positions, indices, list);

	//list->StopRecording();
	//list->Submit(nullptr);

	//std::vector<GFX::UUniform> uniforms = {
	//	GFX::UUniform("Transform", GFX::EUniformType::UniformBuffer, GFX::EShaderStage::Vertex, 1),
	//	GFX::UUniform("Image", GFX::EUniformType::CombinedImageSampler, GFX::EShaderStage::Fragment, 1)
	//};

	//layoutPartition = GFX::CreateLayoutPartition(uniforms);
	//resource = layoutPartition->CreateResources();

	//std::vector<GFX::UDescriptorWrite> writes = {
	//	GFX::UDescriptorWrite("Transform", uniformBuffer, nullptr, nullptr, 0),
	//	GFX::UDescriptorWrite("Image", nullptr, texture, sampler, 0)
	//};

	//resource->WriteUniform(writes);

	//pipeline = GFX::CreatePipeline(GFX::EPipelineUsage::Graphics, GFX::ERenderStage::Geometry, { vertexInput }, shader, viewport, {});
}

Application::~Application()
{
	delete Window;
	GFX::Terminate();
}

Application& Application::Initialize(const char* name)
{
	verify(!Instance, "Application already created.")

	Instance = new Application(name);
	return *Instance;
}

void Application::Terminate()
{
	delete Instance;
}

void Application::Run()
{
	//ATimestep timestep;
	//float rotation = 0;

	while (ShouldRun)
	{
		//timestep++;
		//std::cout << (uint32_t)(1.f / timestep.GetSeconds()) << "fps\n";

		//rotation += timestep * glm::radians(45.f);
		//glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		//glm::mat4 finalMatrix = Camera.GetCameraMatrix() * modelMatrix;

		//uniformBuffer->UpdateData(&finalMatrix, nullptr);

		Window->OnUpdate();

		//GFX::NextFrame();

		//graphicsPool->ResetLists();
		//GFX::ICmdList* list = graphicsPool->GetList(0);

		//viewport->SwapBuffers();

		//list->BeginRecording(GFX::ERenderStage::Geometry, viewport);

		//GFX::BeginRenderPass(list, viewport, true);

		//GFX::BindViewport(list, viewport);
		//GFX::BindPipeline(list, pipeline);
		//GFX::BindVertexBuffer(list, vertexArray->GetBuffer(), vertexArray->GetVertexRange(), vertexArray->GetVertexInput());
		//GFX::BindIndexBuffer(list, vertexArray->GetBuffer(), vertexArray->GetIndexRange(), vertexArray->GetIndexType());
		//GFX::BindPipelineResources(list, pipeline, resource, 0);
		//GFX::DrawIndexed(list, vertexArray->GetIndexCount(), 1, 0, 0, 0);

		//GFX::EndRenderPass(list);

		//list->StopRecording();

		//list->Submit(viewport->GetSemaphore());

		//viewport->PresentImage(list->GetSemaphore());
	}
}

void Application::OnEvent(EVNT::Event& e)
{
	e.Dispatch<EVNT::WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
	e.Dispatch<EVNT::WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
}

bool Application::OnWindowResize(EVNT::WindowResizeEvent& e)
{
	//viewport->Resize(event.GetWidth(), event.GetHeight());
	//Camera.SetProjectionMatrix((float)event.GetWidth() / (float)event.GetHeight(), 45.f);
	
	return true;
}

bool Application::OnWindowClose(EVNT::WindowCloseEvent& e)
{
	ShouldRun = false;
	return true;
}
