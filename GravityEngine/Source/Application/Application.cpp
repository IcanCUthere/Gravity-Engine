module;
#include "Core/DebugUtils.h"

//#define GLM_FORCE_RADIANS
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

module Application;
import Graphics;

std::unordered_map<GFX::ShaderStageFlags, std::string> getShaders(const char* filePath)
{
	std::fstream file(filePath);
	if (!file) {
		std::cout << "Could not open file!\n";
		return {};
	}

	GFX::ShaderStageFlags currentShader = GFX::SHADER_STAGE_VERTEX_BIT;
	std::unordered_map<GFX::ShaderStageFlags, std::string> result;

	std::string line;
	while (getline(file, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				currentShader = GFX::SHADER_STAGE_VERTEX_BIT;
			}
			else if (line.find("fragment") != std::string::npos) {
				currentShader = GFX::SHADER_STAGE_FRAGMENT_BIT;
			}
		}
		else {
			result[currentShader] += line + '\n';
		}
	}

	return result;
}

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

	Window = PLTF::CreateWindow(resX, resY, name);
	Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	GFX::Initialize(GFX::API::Vulkan);

	GFX::AttachmentDescription attachmentDescriptions[] = { 
		GFX::InitAttachmentDescription(GFX::FORMAT_B8G8R8A8_UNORM, GFX::SAMPLE_COUNT_1_BIT, GFX::LOAD_OP_CLEAR, GFX::STORE_OP_STORE, GFX::LOAD_OP_DONT_CARE, GFX::STORE_OP_DONT_CARE, GFX::IMAGE_LAYOUT_UNDEFINED, GFX::IMAGE_LAYOUT_PRESENT_SRC),
		GFX::InitAttachmentDescription(GFX::FORMAT_D16_UNORM, GFX::SAMPLE_COUNT_1_BIT, GFX::LOAD_OP_CLEAR, GFX::STORE_OP_DONT_CARE, GFX::LOAD_OP_DONT_CARE, GFX::STORE_OP_DONT_CARE, GFX::IMAGE_LAYOUT_UNDEFINED, GFX::IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
	};

	GFX::AttachmentReference colorReferences[] = {
		GFX::InitAttachmentReference(0, GFX::IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
	};
	GFX::AttachmentReference depthStencilReference = GFX::InitAttachmentReference(1, GFX::IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

	GFX::SubpassDescription subpassDescriptions[] = {
		GFX::InitSubpassDescription(GFX::PIPELINE_BIND_POINT_GRAPHICS, nullptr, 0, colorReferences, nullptr, 1, &depthStencilReference, nullptr, 0)
	};

	GFX::SubpassDependency subpassDependencies[] = {
		GFX::InitSubpassDependency(~0U, 0, GFX::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, GFX::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, (GFX::AccessFlags)0, GFX::ACCESS_COLOR_ATTACHMENT_WRITE_BIT, (GFX::DependencyFlags)0)
	};

	GFX::CreateRenderPass(renderPass, GFX::InitRenderPassCreateInfo(
		attachmentDescriptions, 2,
		subpassDescriptions, 1,
		subpassDependencies, 1
	));

	uint32_t layerCount = 1, imageCount = 2, swapWidth = resX, swapHeight = resY;

	GFX::CreateSurface(surface, Window->GetNativeWindow(), Window->GetModule(), Window->GetMonitor());
	GFX::CreateSwapchain(swapchain, nullptr, surface, &presentQueue, &layerCount, &imageCount, &swapWidth, &swapHeight);
	GFX::GetSwapchainImages(images, imageCount, swapchain);

	
	GFX::CreateImage(depthBuffer, GFX::InitImageCreateInfo(
		GFX::IMAGE_TYPE_2D,
		GFX::FORMAT_D16_UNORM,
		{ swapWidth, swapHeight, 1 },
		1,
		layerCount,
		GFX::SAMPLE_COUNT_1_BIT,
		GFX::IMAGE_TILING_OPTIMAL,
		GFX::IMAGE_LAYOUT_UNDEFINED,
		GFX::IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	));

	GFX::CreateImageView(views[2], GFX::InitImageViewCreateInfo(
		depthBuffer,
		GFX::IMAGE_VIEW_TYPE_2D,
		GFX::FORMAT_D16_UNORM,
		GFX::InitImageSubresourceRange(
			GFX::IMAGE_ASPECT_DEPTH_BIT,
			0,
			1,
			0,
			layerCount
		)
	));

	GFX::ImageSubresourceRange colorRange = GFX::InitImageSubresourceRange(
		GFX::IMAGE_ASPECT_COLOR_BIT,
		0,
		1,
		0,
		layerCount
	);

	for (uint32_t i = 0; i < 2; i++) {
		GFX::CreateImageView(views[i], GFX::InitImageViewCreateInfo(
			images[i],
			GFX::IMAGE_VIEW_TYPE_2D,
			GFX::FORMAT_B8G8R8A8_UNORM,
			colorRange
		));

		GFX::ImageView attachments[2] = { views[i], views[2] };

		GFX::CreateFramebuffer(framebuffers[i], GFX::InitFramebufferCreateInfo(
			renderPass,
			attachments,
			2,
			swapWidth,
			swapHeight,
			layerCount
		));
	}


	GFX::GetRenderQueue(renderQueue, renderQueueIndex);

	
	GFX::CreateBuffer(stagingBuffer, GFX::InitBufferCreateInfo(
		sizeof(positions) + sizeof(indices),
		GFX::BUFFER_USAGE_TRANSFER_SRC_BIT,
		GFX::MEMORY_USAGE_CPU_TO_GPU
	));

	
	GFX::CreateBuffer(vertexBuffer, GFX::InitBufferCreateInfo(
		sizeof(positions),
		GFX::BUFFER_USAGE_VERTEX_BUFFER_BIT | GFX::BUFFER_USAGE_TRANSFER_DST_BIT,
		GFX::MEMORY_USAGE_GPU_ONLY
	));

	
	GFX::CreateBuffer(indexBuffer, GFX::InitBufferCreateInfo(
		sizeof(indices),
		GFX::BUFFER_USAGE_INDEX_BUFFER_BIT | GFX::BUFFER_USAGE_TRANSFER_DST_BIT,
		GFX::MEMORY_USAGE_GPU_ONLY
	));

	GFX::MemoryCopyData memoryCopies[] = { { positions, 0, sizeof(positions) } , { indices, sizeof(positions), sizeof(indices) } };
	GFX::UploadMemory(stagingBuffer, memoryCopies, sizeof(memoryCopies) / sizeof(*memoryCopies));

//	uniformBuffer = new AUniformBuffer(sizeof(glm::mat4));
//	texture = new ATexture(GFX::USize3D{ (uint32_t)texWidth, (uint32_t)texHeight, 1 }, GFX::Format::R8G8B8A8_SRGB);
//
//	viewport = GFX::CreateViewport(Window->GetNativeWindow(), resX, resY);

	auto shaderCodes = getShaders("Resources/shader.glsl");

	GFX::ShaderCompiler shaderCompiler;
	GFX::CreateShaderCompiler(shaderCompiler);

	GFX::CreateShader(shaders[0], shaderCompiler, GFX::SHADER_STAGE_VERTEX_BIT, shaderCodes[GFX::SHADER_STAGE_VERTEX_BIT].c_str(), (uint32_t)shaderCodes[GFX::SHADER_STAGE_VERTEX_BIT].size());
	GFX::CreateShader(shaders[1], shaderCompiler, GFX::SHADER_STAGE_FRAGMENT_BIT, shaderCodes[GFX::SHADER_STAGE_FRAGMENT_BIT].c_str(), (uint32_t)shaderCodes[GFX::SHADER_STAGE_FRAGMENT_BIT].size());

	GFX::DestroyShaderCompiler(shaderCompiler);

	
	GFX::CreateCmdPool(renderPool, GFX::InitCmdPoolCreateInfo(
		renderQueueIndex
	));

	
	GFX::CreateCmdLists(&cmdList, GFX::InitCmdListsCreateInfo(
		renderPool,
		GFX::CMD_LIST_LEVEL_PRIMARY,
		1
	));

	GFX::BeginRecording(cmdList, GFX::InitBeginRecordingInfo(
		renderPass,
		0,
		framebuffers[0],
		GFX::CMD_LIST_USAGE_ONE_TIME_SUBMIT_BIT
	));

	//GFX::UImageBarrier barrier1{ GFX::AccessFlags::None, GFX::AccessFlags::TransferWrite, texture,  GFX::ImageLayout::TransferDestinationOptimal };
	//GFX::UImageBarrier barrier2{ GFX::AccessFlags::TransferWrite, GFX::AccessFlags::ShaderRead, texture,  GFX::ImageLayout::ShaderReadOnlyOptimal };

	//GFX::InsertPipelineBarriers(list, GFX::EPipelineStage::TopOfPipe, GFX::EPipelineStage::Transfer, {}, {}, { barrier1 });
	//texture->UpdateTextureData(pixels, texWidth * texHeight * 4, list);
	//GFX::InsertPipelineBarriers(list, GFX::EPipelineStage::Transfer, GFX::EPipelineStage::FragmentShader, {}, {}, { barrier2 } );

	GFX::SemaphoreTimelineInfo semaphoreTimelineInfo = GFX::InitSemaphoreTimelineInfo(0, GFX::SEMAPHORE_TYPE_TIMELINE);
	GFX::CreateSemaphore(timelineSemaphore, &semaphoreTimelineInfo);
	GFX::CreateSemaphore(binarySemaphore, nullptr);

	GFX::BufferCopyData bufferCopies[] = { GFX::InitBufferCopyData(0, 0, sizeof(positions)), GFX::InitBufferCopyData(sizeof(positions), 0, sizeof(indices)) };
	GFX::CopyBuffer(cmdList, stagingBuffer, vertexBuffer, &bufferCopies[0], 1);
	GFX::CopyBuffer(cmdList, stagingBuffer, indexBuffer, &bufferCopies[1], 1);

	GFX::StopRecording(cmdList);

	uint64_t signalValue = 1;
	GFX::PipelineStageFlags waitFlag = GFX::PIPELINE_STAGE_TRANSFER_BIT;
	GFX::SubmitTimelineInfo timelineInfo = GFX::InitSubmitTimelineInfo(nullptr, 0, &signalValue, 1);
	GFX::SubmitInfo submits[] = { GFX::InitSubmitInfo(&cmdList, &waitFlag, 1, nullptr, 0, &timelineSemaphore, 1, &timelineInfo) };
	GFX::SubmitCmdLists(renderQueue, submits, 1);

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

	GFX::DescriptorLayoutBinding descriptorBindings[] = { 
		GFX::InitDescriptorLayoutBinding(0, GFX::DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, GFX::SHADER_STAGE_VERTEX_BIT) 
	};
	
	GFX::CreateDescriptorLayout(descriptorLayout, GFX::InitDescriptorLayoutCreateInfo(descriptorBindings, 1));

	GFX::CreatePipelineLayout(layout, GFX::InitPipelineLayoutCreateInfo(nullptr, 0, nullptr, 0)); //(&descriptorLayout, 1, nullptr, 0));

	GFX::VertexBinding bindings[] = { 
		GFX::InitVertexBinding(0, 20, GFX::INPUT_RATE_VERTEX) 
	};
	GFX::VertexAttribute attributes[] = { 
		GFX::InitVertexAttribute(0, 0, 0, GFX::FORMAT_R32G32B32_SFLOAT), 
		GFX::InitVertexAttribute(0, 1, 12, GFX::FORMAT_R32G32_SFLOAT) 
	};

	GFX::Viewport viewports[] = { GFX::InitViewport(0, 0, resX, resY, 0., 1.) };
	GFX::Scissor scissors[] = { GFX::InitScissor(resX, resY, 0, 0) };

	GFX::ColorBlendAttachmentState colorState = { GFX::InitColorBlendAttachmentState(false, GFX::BLEND_OP_ADD, GFX::BLEND_OP_ADD, 
		GFX::COLOR_COMPONENT_R_BIT | GFX::COLOR_COMPONENT_G_BIT | GFX::COLOR_COMPONENT_B_BIT | GFX::COLOR_COMPONENT_A_BIT, 
		GFX::BLEND_FACTOR_ONE, GFX::BLEND_FACTOR_ZERO, GFX::BLEND_FACTOR_ONE, GFX::BLEND_FACTOR_ZERO) };
	float blendConstants[] = { 1., 1., 1., 1. };

	GFX::DynamicState dynamicStates[] = { GFX::DYNAMIC_STATE_VIEWPORT, GFX::DYNAMIC_STATE_SCISSOR };

	GFX::ShaderStageInfo stageInfos[] = { 
		GFX::InitShaderStageInfo(shaders[0], GFX::SHADER_STAGE_VERTEX_BIT, "main"), 
		GFX::InitShaderStageInfo(shaders[1], GFX::SHADER_STAGE_FRAGMENT_BIT, "main")
	};

	GFX::GraphicsPipelineCreateInfo createInfo = GFX::InitGraphicsPipelineCreateInfo(
		layout, 
		renderPass, 0,
		stageInfos, 2,
		GFX::InitVertexInputInfo(nullptr, 0, nullptr, 0), //(bindings, 1, attributes, 2),
		GFX::InitInputAssemblyInfo(GFX::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, false),
		GFX::InitTessellationInfo(0),
		GFX::InitViewportInfo(viewports, 1, scissors, 1),
		GFX::InitRasterizationInfo(GFX::POLYGON_MODE_FILL, GFX::CULL_MODE_BACK_BIT, GFX::FRONT_FACE_CLOCKWISE, false, false, false, 0., 0., 0., 0.),
		GFX::InitMultisamplingInfo(GFX::SAMPLE_COUNT_1_BIT, false, false, false, 1.),
		GFX::InitDepthStencilInfo(true, true, false, false, GFX::COMPARE_OP_LESS, 
			GFX::InitStencilOpState(GFX::STENCIL_OP_KEEP, GFX::STENCIL_OP_KEEP, GFX::STENCIL_OP_KEEP, GFX::COMPARE_OP_ALWAYS, 0, 0, 0),
			GFX::InitStencilOpState(GFX::STENCIL_OP_KEEP, GFX::STENCIL_OP_KEEP, GFX::STENCIL_OP_KEEP, GFX::COMPARE_OP_ALWAYS, 0, 0, 0),
			0., 1.),
		GFX::InitColorBlendInfo(false, GFX::LOGIC_OP_COPY, &colorState, 1, blendConstants),
		GFX::InitDynamicInfo(dynamicStates, 2));

	GFX::CreateGraphicsPipelines(&pipeline, &createInfo, 1);
}

Application::~Application()
{
	GFX::WaitSemaphores(&timelineSemaphore, &semaphoreValue, 1);
	GFX::DestroySemaphore(timelineSemaphore);
	GFX::DestroySemaphore(binarySemaphore);

	GFX::DestroyPipeline(pipeline);
	GFX::DestroyPipelineLayout(layout);
	GFX::DestroyDescriptorLayout(descriptorLayout);
	for (uint32_t i = 0; i < 2; i++) {
		GFX::DestroyShader(shaders[i]);
	}
	GFX::DestroyCmdPool(renderPool);
	GFX::DestroyBuffer(indexBuffer);
	GFX::DestroyBuffer(vertexBuffer);
	GFX::DestroyBuffer(stagingBuffer);
	for (uint32_t i = 0; i < 2; i++) {
		GFX::DestroyFramebuffer(framebuffers[i]);
	}
	for (uint32_t i = 0; i < 3; i++) {
		GFX::DestroyImageView(views[i]);
	}
	GFX::DestroySwapchain(swapchain);
	GFX::DestroySurface(surface);
	GFX::DestroyImage(depthBuffer);
	GFX::DestroyRenderPass(renderPass);

	GFX::Terminate();
	
	delete Window;
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
	uint32_t imageIndex;

	while (ShouldRun)
	{


		//timestep++;
		//std::cout << (uint32_t)(1.f / timestep.GetSeconds()) << "fps\n";

		//rotation += timestep * glm::radians(45.f);
		//glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		//glm::mat4 finalMatrix = Camera.GetCameraMatrix() * modelMatrix;

		//uniformBuffer->UpdateData(&finalMatrix, nullptr);

		Window->OnUpdate();

		
		GFX::GetNextImage(swapchain, binarySemaphore, &imageIndex);

		GFX::WaitSemaphores(&timelineSemaphore, &semaphoreValue, 1);
		GFX::ResetCmdPool(renderPool);

		GFX::BeginRecording(cmdList, GFX::InitBeginRecordingInfo(
			renderPass,
			0,
			framebuffers[imageIndex],
			GFX::CMD_LIST_USAGE_ONE_TIME_SUBMIT_BIT
		));
		
		const float clearColor[4] = { 0.f, 0.f, 0.f, 1.f };
		GFX::ClearValue clearValues[] = { GFX::InitClearValue(clearColor, nullptr, nullptr, 0.f, 0), GFX::InitClearValue(nullptr, nullptr, nullptr, 1.f, 0) };
		GFX::Viewport viewport = GFX::InitViewport(0.f, 0.f, 1000.f, 1000.f, 0.f, 1.f);
		GFX::Scissor scissor = GFX::InitScissor(1000, 1000, 0, 0);

		GFX::BeginRenderPass(cmdList, GFX::InitRenderPassBeginInfo(
			renderPass,
			framebuffers[imageIndex],
			scissor,
			clearValues, 2
		), true);

		GFX::BindViewports(cmdList, &viewport, 1, 0);
		GFX::BindScissors(cmdList, &scissor, 1, 0);
		GFX::BindPipeline(cmdList, pipeline, GFX::PIPELINE_BIND_POINT_GRAPHICS);
		GFX::Draw(cmdList, 3, 1, 0, 0);

		GFX::EndRenderPass(cmdList);
		GFX::StopRecording(cmdList);

		GFX::Semaphore signalSemaphores[2] = {timelineSemaphore, binarySemaphore};
		GFX::PipelineStageFlags stage = GFX::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		GFX::SubmitTimelineInfo timelineInfo = GFX::InitSubmitTimelineInfo(nullptr, 0, &(++semaphoreValue), 2);
			GFX::SubmitInfo submitInfo = GFX::InitSubmitInfo(&cmdList, &stage, 1, &binarySemaphore, 1, signalSemaphores, 2, &timelineInfo);
		GFX::SubmitCmdLists(renderQueue, &submitInfo, 1);

		GFX::PresentImage(presentQueue, GFX::InitPresentInfo(
			&swapchain,
			&imageIndex,
			1,
			&binarySemaphore,
			1
		));
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
