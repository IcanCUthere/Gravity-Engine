module;
#include "Core/DebugUtils.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


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

float positions[48] = {
	-0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f,
	 0.5f,  0.5f, 0.5f, 0.f, 0.f, 1.f,
	-0.5f,  0.5f, 0.5f, 0.f, 1.f, 1.f,
	 0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f,

	-0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f,
	 0.5f,  0.5f, 0.0f, 0.f, 0.f, 1.f,
	-0.5f,  0.5f, 0.0f, 0.f, 1.f, 1.f,
	 0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f,
};

uint32_t indices[12] = {
	2, 1, 0,
	0, 1, 3,

	6, 5, 4,
	4, 5, 7,
};

glm::mat4 matrix(1.f);

Application::Application(const char* name)
	: camera(glm::vec3(2.f, 2.f, 2.f), glm::vec3(0.f, 0.f, 0.f), resX / resY, 45.f)
{
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
		GFX::InitSubpassDependency(~0U, 0, GFX::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, GFX::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, GFX::ACCESS_NONE, GFX::ACCESS_COLOR_ATTACHMENT_WRITE_BIT, GFX::DEPENDENCY_NONE)
	};

	GFX::CreateRenderPass(renderPass, GFX::InitRenderPassCreateInfo(
		attachmentDescriptions, 2,
		subpassDescriptions, 1,
		subpassDependencies, 1
	));

	viewport = new Viewport<MAX_IMAGE_COUNT>(resX, resY, MAX_IMAGE_COUNT, 1, renderPass, std::bind(&Application::OnEvent, this, std::placeholders::_1));

	GFX::GetRenderQueue(renderQueue);

	for (uint32_t i = 0; i < MAX_IMAGE_COUNT; i++) {
		GFX::CreateCmdPool(cmdPools[i], GFX::InitCmdPoolCreateInfo(
			renderQueue
		));

		GFX::CreateCmdLists(&cmdLists[i], GFX::InitCmdListsCreateInfo(
			cmdPools[i],
			GFX::CMD_LIST_LEVEL_PRIMARY,
			1
		));

		GFX::CreateSemaphore(binarySemaphores[i], nullptr);
	}

	GFX::SemaphoreTimelineInfo semaphoreTimelineInfo = GFX::InitSemaphoreTimelineInfo(0, GFX::SEMAPHORE_TYPE_TIMELINE);
	GFX::CreateSemaphore(timelineSemaphore, &semaphoreTimelineInfo);
	
	
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load("Resources\\texture.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

	GFX::CreateBuffer(stagingBuffer, GFX::InitBufferCreateInfo(
		sizeof(positions) + sizeof(indices) + (texWidth * texHeight * 4),
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

	GFX::CreateBuffer(uniformBuffer, GFX::InitBufferCreateInfo(
		sizeof(glm::mat4),
		GFX::BUFFER_USAGE_UNIFORM_BUFFER_BIT | GFX::BUFFER_USAGE_TRANSFER_DST_BIT,
		GFX::MEMORY_USAGE_CPU_ONLY
	));

	GFX::CreateImage(image, GFX::InitImageCreateInfo(
		GFX::IMAGE_TYPE_2D,
		GFX::FORMAT_R8G8B8A8_SRGB,
		GFX::InitExtent3D(texWidth, texHeight, 1),
		1, 1,
		GFX::SAMPLE_COUNT_1_BIT,
		GFX::IMAGE_TILING_OPTIMAL,
		GFX::IMAGE_LAYOUT_UNDEFINED,
		GFX::IMAGE_USAGE_TRANSFER_DST_BIT | GFX::IMAGE_USAGE_SAMPLED_BIT
	));

	GFX::ImageSubresourceRange subresource = GFX::InitImageSubresourceRange(GFX::IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1);

	GFX::CreateImageView(imageView, GFX::InitImageViewCreateInfo(
		image, 
		GFX::IMAGE_VIEW_TYPE_2D,
		GFX::FORMAT_R8G8B8A8_SRGB,
		subresource
	));

	GFX::CreateSampler(sampler, GFX::InitSamplerCreateInfo(
		GFX::FILTER_LINEAR,
		GFX::FILTER_LINEAR,
		GFX::MIPMAP_MODE_LINEAR,
		GFX::ADDRESS_MODE_REPEAT,
		GFX::ADDRESS_MODE_REPEAT,
		GFX::ADDRESS_MODE_REPEAT,
		true, 1.f,
		0.f, 0.f, 0.f,
		true, GFX::COMPARE_OP_ALWAYS
	));

	GFX::MemoryCopyData memoryCopies[] = { 
		{ positions, 0, sizeof(positions) } , 
		{ indices, sizeof(positions), sizeof(indices) }, 
		{ pixels, sizeof(positions) + sizeof(indices), (texWidth * texHeight * 4u) },
		{ &matrix, 0, sizeof(matrix) } 
	};
	GFX::UploadMemory(stagingBuffer, &memoryCopies[0], 3);
	GFX::UploadMemory(uniformBuffer, &memoryCopies[3], 1);


	GFX::BeginRecording(cmdLists[0], GFX::InitBeginRecordingInfo(
		GFX::CMD_LIST_USAGE_ONE_TIME_SUBMIT_BIT,
		nullptr
	));

	GFX::ImageBarrier barriers[] = { 
		GFX::InitImageBarrier(GFX::ACCESS_NONE, GFX::ACCESS_TRANSFER_WRITE_BIT, ~0U, ~0U, image, GFX::IMAGE_LAYOUT_UNDEFINED, GFX::IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, subresource),
		GFX::InitImageBarrier(GFX::ACCESS_TRANSFER_WRITE_BIT, GFX::ACCESS_SHADER_READ_BIT, ~0U, ~0U, image, GFX::IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, GFX::IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, subresource)
	};

	GFX::BufferCopyData bufferCopies[] = { GFX::InitBufferCopyData(0, 0, sizeof(positions)), GFX::InitBufferCopyData(sizeof(positions), 0, sizeof(indices)) };
	GFX::BufferImageCopyData imageCopies[] = { GFX::InitBufferImageCopyData(0, 0, 0, GFX::InitOffset3D(0,0,0), GFX::InitExtent3D(texWidth, texHeight, 1), GFX::InitImageSubresourceLayers(GFX::IMAGE_ASPECT_COLOR_BIT, 0, 0, 1)) };
	
	GFX::InsertBarrier(cmdLists[0], GFX::PIPELINE_STAGE_TOP_OF_PIPE_BIT, GFX::PIPELINE_STAGE_TRANSFER_BIT, GFX::DEPENDENCY_NONE, nullptr, 0, nullptr, 0, &barriers[0], 1);
	GFX::CopyBuffer(cmdLists[0], stagingBuffer, vertexBuffer, &bufferCopies[0], 1);
	GFX::CopyBuffer(cmdLists[0], stagingBuffer, indexBuffer, &bufferCopies[1], 1);
	GFX::CopyBufferToImage(cmdLists[0], stagingBuffer, image, GFX::IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, imageCopies, 1);
	GFX::InsertBarrier(cmdLists[0], GFX::PIPELINE_STAGE_TRANSFER_BIT, GFX::PIPELINE_STAGE_FRAGMENT_SHADER_BIT, GFX::DEPENDENCY_NONE, nullptr, 0, nullptr, 0, &barriers[1], 1);

	GFX::StopRecording(cmdLists[0]);

	uint64_t signalValue = 1;
	GFX::PipelineStageFlags waitFlag = GFX::PIPELINE_STAGE_TRANSFER_BIT;
	GFX::SubmitTimelineInfo timelineInfo = GFX::InitSubmitTimelineInfo(nullptr, 0, &signalValue, 1);
	GFX::SubmitInfo submits[] = { GFX::InitSubmitInfo(&cmdLists[0], &waitFlag, 1, nullptr, 0, &timelineSemaphore, 1, &timelineInfo) };
	GFX::SubmitCmdLists(renderQueue, submits, 1);

	auto shaderCodes = getShaders("Resources/shader4.glsl");

	GFX::ShaderCompiler shaderCompiler;
	GFX::CreateShaderCompiler(shaderCompiler);

	GFX::CreateShader(shaders[0], shaderCompiler, GFX::SHADER_STAGE_VERTEX_BIT, shaderCodes[GFX::SHADER_STAGE_VERTEX_BIT].c_str(), (uint32_t)shaderCodes[GFX::SHADER_STAGE_VERTEX_BIT].size());
	GFX::CreateShader(shaders[1], shaderCompiler, GFX::SHADER_STAGE_FRAGMENT_BIT, shaderCodes[GFX::SHADER_STAGE_FRAGMENT_BIT].c_str(), (uint32_t)shaderCodes[GFX::SHADER_STAGE_FRAGMENT_BIT].size());

	GFX::DestroyShaderCompiler(shaderCompiler);

	GFX::DescriptorLayoutBinding descriptorBindings[] = { 
		GFX::InitDescriptorLayoutBinding(0, GFX::DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, GFX::SHADER_STAGE_VERTEX_BIT),
		GFX::InitDescriptorLayoutBinding(1, GFX::DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, GFX::SHADER_STAGE_FRAGMENT_BIT)
	};
	
	GFX::CreateDescriptorLayout(descriptorLayout, GFX::InitDescriptorLayoutCreateInfo(descriptorBindings, 2));


	GFX::DescriptorPoolSize poolSizes[] = { 
		GFX::InitDescriptorPoolSize(GFX::DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1),
		GFX::InitDescriptorPoolSize(GFX::DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1)
	};
	GFX::CreateDescriptorPool(descriptorPool, GFX::InitDescriptorPoolCreateInfo(poolSizes, 1, 10));

	GFX::CreatePipelineLayout(layout, GFX::InitPipelineLayoutCreateInfo(&descriptorLayout, 1, nullptr, 0));

	GFX::CreateDescriptorSets(&descriptorSet, GFX::InitDescriptorSetsCreateInfo(descriptorPool, &descriptorLayout, 1));

	GFX::DescriptorBufferInfo descBufInfo = GFX::InitDescriptorBufferInfo(uniformBuffer, 0, sizeof(glm::mat4));
	GFX::DescriptorImageInfo descImgInfo = GFX::InitDescriptorImageInfo(imageView, sampler, GFX::IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	GFX::DescriptorWriteData writeData[] =  {
		GFX::InitDescriptorWriteData(descriptorSet, 0, 0, GFX::DESCRIPTOR_TYPE_UNIFORM_BUFFER, nullptr, &descBufInfo, 1),
		GFX::InitDescriptorWriteData(descriptorSet, 1, 0, GFX::DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, &descImgInfo, nullptr, 1)
	};
	GFX::WriteDescriptorSet(writeData, 2);


	GFX::VertexBinding bindings[] = { 
		GFX::InitVertexBinding(0, 24, GFX::INPUT_RATE_VERTEX) 
	};
	GFX::VertexAttribute attributes[] = { 
		GFX::InitVertexAttribute(0, 0, 0, GFX::FORMAT_R32G32B32_SFLOAT), 
		GFX::InitVertexAttribute(0, 1, 16, GFX::FORMAT_R32G32_SFLOAT) 
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

	GFX::VertexInputInfo vertexInputInfo = GFX::InitVertexInputInfo(bindings, 1, attributes, 2);
	GFX::InputAssemblyInfo inputAssemblyInfo = GFX::InitInputAssemblyInfo(GFX::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, false);
	GFX::TessellationInfo tesselationInfo = GFX::InitTessellationInfo(0);
	GFX::ViewportInfo viewportInfo = GFX::InitViewportInfo(viewports, 1, scissors, 1);
	GFX::RasterizationInfo rasterizationInfo = GFX::InitRasterizationInfo(GFX::POLYGON_MODE_FILL, GFX::CULL_MODE_BACK_BIT, GFX::FRONT_FACE_COUNTER_CLOCKWISE, false, false, false, 0., 0., 0., 0.);
	GFX::MultisamplingInfo multisamplingInfo = GFX::InitMultisamplingInfo(GFX::SAMPLE_COUNT_1_BIT, false, false, false, 1.);
	GFX::DepthStencilInfo depthStencilInfo = GFX::InitDepthStencilInfo(true, true, false, false, GFX::COMPARE_OP_LESS,
		GFX::InitStencilOpState(GFX::STENCIL_OP_KEEP, GFX::STENCIL_OP_KEEP, GFX::STENCIL_OP_KEEP, GFX::COMPARE_OP_ALWAYS, 0, 0, 0),
		GFX::InitStencilOpState(GFX::STENCIL_OP_KEEP, GFX::STENCIL_OP_KEEP, GFX::STENCIL_OP_KEEP, GFX::COMPARE_OP_ALWAYS, 0, 0, 0),
		0., 1.);
	GFX::ColorBlendInfo colorBlendInfo = GFX::InitColorBlendInfo(false, GFX::LOGIC_OP_COPY, &colorState, 1, blendConstants);
	GFX::DynamicInfo dynamicInfo = GFX::InitDynamicInfo(dynamicStates, 2);

	GFX::GraphicsPipelineCreateInfo createInfo = GFX::InitGraphicsPipelineCreateInfo(
		layout, 
		renderPass, 0,
		stageInfos, 2,
		vertexInputInfo,
		inputAssemblyInfo,
		tesselationInfo,
		viewportInfo,
		rasterizationInfo,
		multisamplingInfo,
		depthStencilInfo,
		colorBlendInfo,
		dynamicInfo);

	GFX::CreateGraphicsPipelines(&pipeline, &createInfo, 1);
}

Application::~Application()
{
	GFX::WaitSemaphores(&timelineSemaphore, &semaphoreValue, 1);
	GFX::DestroySemaphore(timelineSemaphore);
	for (uint32_t i = 0; i < MAX_IMAGE_COUNT; i++) {
		GFX::DestroySemaphore(binarySemaphores[i]);
		GFX::DestroyCmdPool(cmdPools[i]);
	}
	GFX::DestroyPipeline(pipeline);
	GFX::DestroyPipelineLayout(layout);
	GFX::DestroyDescriptorLayout(descriptorLayout);
	GFX::DestroyDescriptorPool(descriptorPool);

	for (uint32_t i = 0; i < 2; i++) {
		GFX::DestroyShader(shaders[i]);
	}

	GFX::DestroySampler(sampler);
	GFX::DestroyImageView(imageView);
	GFX::DestroyImage(image);
	GFX::DestroyBuffer(uniformBuffer);
	GFX::DestroyBuffer(indexBuffer);
	GFX::DestroyBuffer(vertexBuffer);
	GFX::DestroyBuffer(stagingBuffer);
	GFX::DestroyRenderPass(renderPass);

	delete viewport;

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
	Timestep timestep;
	float rotation = 0;
	uint32_t imageIndex = 0;
	
	while (ShouldRun)
	{
		timestep++;
		std::cout << (uint32_t)(1.f / timestep.GetSeconds()) << "fps\n";

		rotation += timestep * glm::radians(45.f);
		glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 finalMatrix = camera.GetCameraMatrix() * modelMatrix;

		GFX::MemoryCopyData memoryCopie = { &finalMatrix, 0, sizeof(finalMatrix) };
		GFX::UploadMemory(uniformBuffer, &memoryCopie, 1);


		viewport->GetNextImage(binarySemaphores[imageIndex]);

		uint64_t waitValue = (1 > semaphoreValue - 1 ? 1 : semaphoreValue - 1);
		GFX::WaitSemaphores(&timelineSemaphore, &waitValue, 1);
		GFX::ResetCmdPool(cmdPools[imageIndex]);

		GFX::InheritanceInfo inheritance = GFX::InitInheritanceInfo(renderPass, 0, viewport->GetFramebuffer());
		GFX::BeginRecording(cmdLists[imageIndex], GFX::InitBeginRecordingInfo(
			GFX::CMD_LIST_USAGE_ONE_TIME_SUBMIT_BIT,
			&inheritance
		));
		
		const float clearColor[4] = { 0.f, 0.f, 0.f, 1.f };
		GFX::ClearValue clearValues[] = { GFX::InitClearValue(clearColor, nullptr, nullptr, 0.f, 0), GFX::InitClearValue(nullptr, nullptr, nullptr, 1.f, 0) };
		GFX::Viewport viewports = GFX::InitViewport(0.f, 0.f, (float)viewport->GetWidth(), (float)viewport->GetHeight(), 0.f, 1.f);
		GFX::Scissor scissor = GFX::InitScissor(viewport->GetWidth(), viewport->GetHeight(), 0, 0);

		GFX::BeginRenderPass(cmdLists[imageIndex], GFX::InitRenderPassBeginInfo(
			renderPass,
			viewport->GetFramebuffer(),
			scissor,
			clearValues, 2
		), true);

		GFX::BindViewports(cmdLists[imageIndex], &viewports, 1, 0);
		GFX::BindScissors(cmdLists[imageIndex], &scissor, 1, 0);
		GFX::BindPipeline(cmdLists[imageIndex], pipeline, GFX::PIPELINE_BIND_POINT_GRAPHICS);
		GFX::BindVertexBuffer(cmdLists[imageIndex], vertexBuffer, 0, 1, 0);
		GFX::BindIndexBuffer(cmdLists[imageIndex], indexBuffer, GFX::INDEX_TYPE_UINT32, 0);
		GFX::BindDescriptorSets(cmdLists[imageIndex], layout, &descriptorSet, 1, 0, GFX::PIPELINE_BIND_POINT_GRAPHICS);
		GFX::DrawIndexed(cmdLists[imageIndex], 12, 1, 0, 0, 0);
		GFX::EndRenderPass(cmdLists[imageIndex]);
		GFX::StopRecording(cmdLists[imageIndex]);

		GFX::Semaphore signalSemaphores[2] = { timelineSemaphore, binarySemaphores[imageIndex] };
		GFX::PipelineStageFlags stage = GFX::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		GFX::SubmitTimelineInfo timelineInfo = GFX::InitSubmitTimelineInfo(nullptr, 0, &(++semaphoreValue), 2);
		GFX::SubmitInfo submitInfo = GFX::InitSubmitInfo(&cmdLists[imageIndex], &stage, 1, &binarySemaphores[imageIndex], 1, signalSemaphores, 2, &timelineInfo);
		GFX::SubmitCmdLists(renderQueue, &submitInfo, 1);

		viewport->PresentImage(&binarySemaphores[imageIndex], 1);

		imageIndex = (imageIndex + 1) % MAX_IMAGE_COUNT;
	}
}

void Application::OnEvent(EVNT::Event& e)
{
	e.Dispatch<EVNT::WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
	e.Dispatch<EVNT::WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
}

bool Application::OnWindowResize(EVNT::WindowResizeEvent& e)
{
	viewport->Resize(e.GetWidth(), e.GetHeight());
	camera.SetProjectionMatrix((float)e.GetWidth() / (float)e.GetHeight(), 45.f);
	
	return true;
}

bool Application::OnWindowClose(EVNT::WindowCloseEvent& e)
{
	ShouldRun = false;
	return true;
}
