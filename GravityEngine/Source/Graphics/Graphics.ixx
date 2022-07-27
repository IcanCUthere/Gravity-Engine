module;
#include "Core/DebugUtils.h"
#include <vulkan/vulkan.h>
#include <shaderc/shaderc.h>

export module Graphics;
import "MemoryAllocator.h";
import stdlib;

#define DEFINE_GFX_FUNCTION(name, parameters, parameterNames, extra) \
inline void Vulkan##name##parameters; \
/*inline void DirectX12##name##parameters;*/ \
/*inline void OpenGL##name##parameters;*/ \
export void name##parameters \
{ \
	extra \
	switch(API) \
	{ \
		case EAPI::Vulkan: Vulkan##name##parameterNames; break; \
		/*case EAPI::DirectX12: DirectX12##name##parameterNames; break;*/ \
		/*case EAPI::OpenGL: OpenGL##name##parameterNames; break;*/ \
		default: THROW_ERROR(); \
	} \
}

#define DEFINE_GFX_FUNCTION_RETURN(returnType, name, parameters, parameterNames) \
inline returnType Vulkan##name##parameters; \
/*inline returnType DirectX12##name##parameters;*/ \
/*inline returnType OpenGL##name##parameters;*/ \
export returnType name##parameters \
{ \
	switch(API) \
	{ \
		case EAPI::Vulkan: return Vulkan##name##parameterNames; \
		/*case EAPI::DirectX12: return DirectX12##name##parameterNames;*/ \
		/*case EAPI::OpenGL: return OpenGL##name##parameterNames;*/ \
		default: THROW_ERROR(); return returnType(); \
	} \
}

namespace GFX
{
	export enum class EAPI
	{
		Vulkan,
		DirectX12,
		OpenGL
	} API;

	export union HBuffer
	{
		struct {
			VkBuffer Buffer;
			VmaAllocation Allocation;
		} VkHandle;
	};

	export union HImage
	{
		struct {
			VkImage Image;
			VmaAllocation Allocation;
		} VkHandle;
	};

	export union HCmdPool
	{
		VkCommandPool VkHandle;
	};

	export union HCmdList
	{
		VkCommandBuffer VkHandle;
	};

	export union HRenderPass
	{
		VkRenderPass VkHandle;
	};

	export union HFramebuffer
	{
		VkFramebuffer VkHandle;
	};

	export union HQueue
	{
		VkQueue VkHandle;
	};

	export union HSemaphore
	{
		VkSemaphore VkHandle;
	};

	export union HDescriptorPool
	{
		VkDescriptorPool VkHandle;
	};

	export union HDescriptorLayout
	{
		VkDescriptorSetLayout VkHandle;
	};

	export union HDescriptorSet
	{
		VkDescriptorSet VkHandle;
	};

	export union HImageView
	{
		VkImageView VkHandle;
	};

	export union HSampler
	{
		VkSampler VkHandle;
	};

	export union HShader
	{
		VkShaderModule VkHandle;
	};

	export union HShaderCompiler
	{
		shaderc_compiler_t VkHandle;
	};

	export union HSurface
	{
		VkSurfaceKHR VkHandle;
	};

	export union HSwapchain
	{
		VkSwapchainKHR VkHandle;
	};

	export union HPipeline
	{
		VkPipeline VkHandle;
	};

	export union HPipelineLayout
	{
		VkPipelineLayout VkHandle;
	};

	export enum EFormat
	{

	};

	export enum ESampleCountFlags
	{

	};

	export enum EBufferUsage
	{

	};

	export enum EMemoryUsage
	{

	};

	export enum ECmdListUsage
	{

	};

	export enum ECmdListLevel
	{

	};

	export enum EBeginRecordingFlags
	{

	};

	export enum EPipelineStageFlags
	{

	};

	export enum EDescriptorType
	{

	};

	export enum EImageLayout
	{

	};

	export enum EImageType
	{

	};

	export enum EImageUsageFlags
	{

	};

	export enum EImageTiling
	{

	};

	export enum EImageAspectFlags
	{

	};

	export enum EImageViewType
	{

	};

	export enum ELoadOp
	{

	};

	export enum EStoreOp
	{

	};

	export enum EPipelineBindPoint
	{

	};

	export enum EAccessFlags
	{

	};

	export enum EDependencyFlags
	{

	};

	export enum EShaderStageFlags
	{

	};

	export enum EFilter
	{

	};

	export enum EAddressMode
	{

	};

	export enum EMipmapMode
	{

	};

	export enum ECompareOp
	{

	};

	export enum EIndexType
	{

	};

	export struct Offset
	{
		int32_t X;
		int32_t Y;
		int32_t Z;
	};

	export struct Extent
	{
		uint32_t X;
		uint32_t Y;
		uint32_t Z;
	};

	export struct MemoryCopyData
	{
		void* Data;
		uint32_t DstOffset;
		uint32_t Size;
	};

	export struct ImageSubresourceLayer
	{
		VkImageSubresourceLayers VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(ImageSubresourceLayer, InitImageSubresourceLayer,
		(EImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t baseLayer, uint32_t layerCount),
		(aspectMask, mipLevel, baseLayer, layerCount))

	export struct ImageSubresourceRange
	{
		VkImageSubresourceRange VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(ImageSubresourceRange, InitImageSubresourceRange,
		(EImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t levelCount, uint32_t baseLayer, uint32_t layerCount),
		(aspectMask, mipLevel, levelCount, baseLayer, layerCount))

	export union BufferCopyData
	{
		VkBufferCopy VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(BufferCopyData, InitBufferCopyData,
		(uint32_t srcOffset, uint32_t dstOffset, uint32_t size),
		(srcOffset, dstOffset, size))

	export union BufferImageCopyData
	{
		VkBufferImageCopy VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(BufferImageCopyData, InitBufferImageCopyData,
		(uint64_t srcOffset, uint32_t rowLength, uint32_t bufferImageHeight, Offset imageOffset, Extent imageExtent, ImageSubresourceLayer subresource),
		(srcOffset, rowLength, bufferImageHeight, imageOffset, imageExtent, subresource))

	export union DescriptorPoolSize
	{
		VkDescriptorPoolSize VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(DescriptorPoolSize, InitDescriptorPoolSize,
		(EDescriptorType type, uint32_t count),
		(type, count))

	export union DescriptorLayoutBinding
	{
		VkDescriptorSetLayoutBinding VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(DescriptorLayoutBinding, InitDescriptorLayoutBinding,
		(uint32_t binding, EDescriptorType type, uint32_t count, uint32_t shaderStageFlags), 
		(binding, type, count, shaderStageFlags))

	export union DescriptorBufferInfo
	{
		VkDescriptorBufferInfo VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(DescriptorBufferInfo, InitDescriptorBufferInfo,
		(HBuffer buffer, uint64_t offset, uint64_t range),
		(buffer, offset, range))

	export union DescriptorImageInfo
	{
		VkDescriptorImageInfo VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(DescriptorImageInfo, InitDescriptorImageInfo,
		(HImageView imageView, HSampler sampler, EImageLayout imageLayout),
		(imageView, sampler, imageLayout))

	export union DescriptorWriteData
	{
		VkWriteDescriptorSet VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(DescriptorWriteData, InitDescriptorWriteData,
		(HDescriptorSet dstSet, uint32_t binding, uint32_t index, EDescriptorType type, DescriptorImageInfo* imageInfo, DescriptorBufferInfo* bufferInfo, uint32_t count),
		(dstSet, binding, index, type, imageInfo, bufferInfo, count))

	export union RPAttachmentDescription
	{
		VkAttachmentDescription VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(RPAttachmentDescription, InitRPAttachmentDescription,
		(EFormat format, ESampleCountFlags sampleCount, ELoadOp lop, EStoreOp sop, ELoadOp stencilLop, EStoreOp stencilSop, EImageLayout initialLayout, EImageLayout finalLayout),
		(format, sampleCount, lop, sop, stencilLop, stencilSop, initialLayout, finalLayout))


	export union RPAttachmentReference
	{
		VkAttachmentReference VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(RPAttachmentReference, InitRPAttachmentReference,
		(uint32_t attachment, EImageLayout layout),
		(attachment, layout))

	export union RPSubpassDescription
	{
		VkSubpassDescription VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(RPSubpassDescription, InitRPSubpassDescription,
		(EPipelineBindPoint bindPoint, RPAttachmentReference* inputs, uint32_t inputCount, RPAttachmentReference* colors, RPAttachmentReference* resolves, uint32_t colorCount, RPAttachmentReference* depthStencil, uint32_t* reserves, uint32_t reserveCount),
		(bindPoint, inputs, inputCount, colors, resolves, colorCount, depthStencil, reserves, reserveCount))

	export union RPSubpassDependency
	{
		VkSubpassDependency VkObject;
	};

	DEFINE_GFX_FUNCTION_RETURN(RPSubpassDependency, InitRPSubpassDependency,
		(uint32_t srcSubpass, uint32_t dstSubpass, EPipelineStageFlags srcStages, EPipelineStageFlags dstStages, EAccessFlags srcAccess, EAccessFlags dstAccess, EDependencyFlags flags),
		(srcSubpass, dstSubpass, srcStages, dstStages, srcAccess, dstAccess, flags))

	union ClearValue 
	{
		VkClearValue VkObject;
	};

	union Scissor
	{
		VkRect2D VkObject;
	};

	union Viewport
	{
		VkViewport VkObject;
	};

	union GraphicsPipelineCreateInfo
	{
		VkGraphicsPipelineCreateInfo VkObject;
	};

	union PipelineLayoutCreateInfo
	{
		VkPipelineLayoutCreateInfo VkObject;
	};

	DEFINE_GFX_FUNCTION(Initialize, 
		(EAPI api), 
		(api), 
		API = api;)

	DEFINE_GFX_FUNCTION(Terminate,
		(),
		(),)

	DEFINE_GFX_FUNCTION(CreateBuffer,
		(HBuffer& handle, uint32_t size, EBufferUsage usage, EMemoryUsage memoryUsage),
		(handle, size, usage, memoryUsage),)

	DEFINE_GFX_FUNCTION(DestroyBuffer,
		(HBuffer handle),
		(handle),)

	DEFINE_GFX_FUNCTION(UploadMemory,
		(HBuffer dstBuffer, MemoryCopyData* copyData, uint32_t count),
		(dstBuffer, copyData, count),)

	DEFINE_GFX_FUNCTION(CreateImage,
		(HImage& handle, uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevels, uint32_t layers, EFormat format, EImageLayout initialLayout, EImageType type, EImageUsageFlags usage, ESampleCountFlags sampleCount, EImageTiling tiling),
		(handle, width, height, depth, mipLevels, layers, format, initialLayout, type, usage, sampleCount, tiling),)

	DEFINE_GFX_FUNCTION(DestroyImage,
		(HImage handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateImageView,
		(HImageView& handle, HImage image, EFormat format, EImageViewType type, ImageSubresourceRange subresource),
		(handle, image, format, type, subresource),)

	DEFINE_GFX_FUNCTION(DestroyImageView,
		(HImageView handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateCmdPool,
		(HCmdPool& handle, uint32_t queueIndex),
		(handle, queueIndex),)

	DEFINE_GFX_FUNCTION(DestroyCmdPool,
		(HCmdPool handle),
		(handle),)

	DEFINE_GFX_FUNCTION(ResetCmdPool,
		(HCmdPool handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateCmdLists,
		(HCmdList* cmdLists, uint32_t count, HCmdPool parentPool, ECmdListLevel listLevel),
		(cmdLists, count, parentPool, listLevel),)

	DEFINE_GFX_FUNCTION(BeginRecording,
		(HCmdList cmdList, HRenderPass renderPass, uint32_t subpass, HFramebuffer framebuffer, EBeginRecordingFlags flags),
		(cmdList, renderPass, subpass, framebuffer, flags),)

	DEFINE_GFX_FUNCTION(StopRecording,
		(HCmdList cmdList),
		(cmdList),)

	DEFINE_GFX_FUNCTION(SubmitCmdLists,
		(HQueue queue, HCmdList* lists, EPipelineStageFlags* stageFlags, uint32_t count, HSemaphore* signalSemaphores, uint32_t signalCount, HSemaphore* waitSemaphores, uint32_t waitCount),
		(queue, lists, stageFlags, count, signalSemaphores, signalCount, waitSemaphores, waitCount),)

	DEFINE_GFX_FUNCTION(ResetCmdList,
		(HCmdList cmdList, bool releaseResources),
		(cmdList, releaseResources),)

	DEFINE_GFX_FUNCTION(CreateDescriptorPool,
		(HDescriptorPool& handle, DescriptorPoolSize* poolSizes, uint32_t poolCount, uint32_t maxSets),
		(handle, poolSizes, poolCount, maxSets),)

	DEFINE_GFX_FUNCTION(DestroyDescriptorPool,
		(HDescriptorPool handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateDescriptorLayout,
		(HDescriptorLayout& handle, DescriptorLayoutBinding* bindings, uint32_t bindingCount),
		(handle, bindings, bindingCount),)

	DEFINE_GFX_FUNCTION(DestroyDescriptorLayout,
		(HDescriptorLayout handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateDescriptorSets,
		(HDescriptorSet* handles, HDescriptorLayout* layouts, uint32_t count, HDescriptorPool parentPool),
		(handles, layouts, count, parentPool),)

	DEFINE_GFX_FUNCTION(WriteDescriptorSet,
		(DescriptorWriteData* writes, uint32_t count),
		(writes, count),)

	DEFINE_GFX_FUNCTION(CreateFramebuffer,
		(HFramebuffer& handle, HRenderPass renderPass, HImageView* attachments, uint32_t attachmentCount, uint32_t width, uint32_t height, uint32_t layers),
		(handle, renderPass, attachments, attachmentCount, width, height, layers),)

	DEFINE_GFX_FUNCTION(DestroyFramebuffer,
		(HFramebuffer handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateRenderPass,
		(HRenderPass& handle, RPAttachmentDescription* attachments, uint32_t attachmentCount, RPSubpassDescription* subpasses, uint32_t subpassCount, RPSubpassDependency* dependencies, uint32_t dependencyCount),
		(handle, attachments, attachmentCount, subpasses, subpassCount, dependencies, dependencyCount),)

	DEFINE_GFX_FUNCTION(DestroyRenderPass,
		(HRenderPass handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateShaderCompiler,
		(HShaderCompiler& handle),
		(handle),)

	DEFINE_GFX_FUNCTION(DestroyShaderCompiler,
		(HShaderCompiler handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateShader,
		(HShader& handle, HShaderCompiler compiler, EShaderStageFlags stage, const char* code, uint32_t size),
		(handle, compiler, stage, code, size),)

	DEFINE_GFX_FUNCTION(DestroyShader,
		(HShader handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateSampler,
		(HSampler& handle, EFilter magFilter, EFilter minFilter, EAddressMode addressMode, EMipmapMode mipMode, float minLod, float maxLod, float lodBias, bool anisotropy, float maxAnisotropy, bool compare, ECompareOp op),
		(handle, magFilter, minFilter, addressMode, mipMode, minLod, maxLod, lodBias, anisotropy, maxAnisotropy, compare, op),)

	DEFINE_GFX_FUNCTION(DestroySampler,
		(HSampler handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateSemaphore,
		(HSemaphore& handle, uint64_t initialValue),
		(handle, initialValue),)

	DEFINE_GFX_FUNCTION(DestroySemaphore,
		(HSemaphore handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateSwapchain,
		(HSwapchain& handle, HSwapchain old, HSurface surface, HQueue* presentQueue, uint32_t* layers, uint32_t* imageCount, uint32_t* width, uint32_t* height),
		(handle, old, surface, presentQueue, layers, imageCount, width, height),)

	DEFINE_GFX_FUNCTION(DestroySwapchain,
		(HSwapchain handle),
		(handle),)



	DEFINE_GFX_FUNCTION(CopyBuffer,
		(HCmdList cmdList, HBuffer srcBuffer, HBuffer dstBuffer, BufferCopyData* copyData, uint32_t count),
		(cmdList, srcBuffer, dstBuffer, copyData, count),)

	DEFINE_GFX_FUNCTION(CopyBufferToImage,
		(HCmdList cmdList, HBuffer srcBuffer, HImage dstImage, EImageLayout currentLayout, BufferImageCopyData* copyData, uint32_t count),
		(cmdList, srcBuffer, dstImage, currentLayout, copyData, count),)

	DEFINE_GFX_FUNCTION(ExecuteCmdLists,
		(HCmdList cmdList, HCmdList* cmdLists, uint32_t count),
		(cmdList, cmdLists, count),)
}