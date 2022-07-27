module;
#include <vulkan/vulkan.h>
#include <shaderc/shaderc.h>
#include "Core/DebugUtils.h"



#ifdef _WIN32
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif

#ifdef _DEBUG

#define VK_VALIDATE(x) \
if(x != VK_SUCCESS) \
{\
	std::cout << "Vulkan error in function: " << __FUNCTION__ << ", line " << __LINE__ << std::endl; __debugbreak(); \
}

#else

#define VK_VALIDATE(x) x;

#endif

#define INIT_INST_FUNC(name) VkContext.##name = (PFN_##name)VkContext.vkGetInstanceProcAddr(VkContext.Instance, #name)
#define INIT_DEV_FUNC(name) VkContext.##name = (PFN_##name)VkContext.vkGetDeviceProcAddr(VkContext.LogicalDevice, #name)

#define ASSERT_HANDLE_SIZE(type, vkType) static_assert(sizeof(type) == sizeof(vkType))

module Graphics;

namespace GFX
{
	VkFormat toVkFormat(EFormat format)
	{
		return (VkFormat)0;
	}

	VkSampleCountFlags toVkSampleCountFlags(ESampleCountFlags sample)
	{
		return 0;
	}

	VkBufferUsageFlags toVkBufferUsage(EBufferUsage usage)
	{
		return 0;
	}

	VmaMemoryUsage toVkMemoryUsage(EMemoryUsage usage)
	{
		return (VmaMemoryUsage)0;
	}

	VkCommandBufferLevel toVkCmdListLevel(ECmdListLevel level)
	{
		return (VkCommandBufferLevel)0;
	}

	VkCommandBufferUsageFlags toVkBeginRecordingFlags(EBeginRecordingFlags flags)
	{
		return 0;
	}

	VkPipelineStageFlags toVkPipelineStages(EPipelineStageFlags flags)
	{
		return 0;
	}

	VkDescriptorType toVkDescriptorType(EDescriptorType type)
	{
		return (VkDescriptorType)0;
	}

	VkImageLayout toVkImageLayout(EImageLayout layout)
	{
		return (VkImageLayout)0;
	}

	VkImageType toVkimageType(EImageType type)
	{
		return (VkImageType)0;
	}

	VkImageTiling toVkImageTiling(EImageTiling tiling)
	{
		return (VkImageTiling)0;
	}

	VkImageUsageFlags toVkImageUsageFlags(EImageUsageFlags flags)
	{
		return 0;
	}

	VkImageAspectFlags toVkImageAspectFlags(EImageAspectFlags flags)
	{
		return 0;
	}

	VkImageViewType toVkImageViewType(EImageViewType type)
	{
		return (VkImageViewType)0;
	}

	VkAttachmentLoadOp toVkLoadOp(ELoadOp op)
	{
		return (VkAttachmentLoadOp)0;
	}

	VkAttachmentStoreOp toVkStoreOp(EStoreOp op)
	{
		return (VkAttachmentStoreOp)0;
	}

	VkPipelineBindPoint toVkPipelineBindPoint(EPipelineBindPoint bindPoint)
	{
		return (VkPipelineBindPoint)0;
	}

	VkAccessFlags toVkAccessMask(EAccessFlags access)
	{
		return (VkAccessFlags)0;
	}

	VkDependencyFlags toVkDependencies(EDependencyFlags flags)
	{
		return 0;
	}

	VkShaderStageFlags toVkShaderStageFlags(EShaderStageFlags flags)
	{
		return 0;
	}

	shaderc_shader_kind toShadercShaderKind(EShaderStageFlags flags)
	{
		return (shaderc_shader_kind)0;
	}

	VkFilter toVkFilter(EFilter filter)
	{
		return (VkFilter)0;
	}

	VkSamplerAddressMode toVkAddressMode(EAddressMode mode)
	{
		return (VkSamplerAddressMode)0;
	}

	VkCompareOp toVkCompareOp(ECompareOp op)
	{
		return (VkCompareOp)0;
	}

	VkSamplerMipmapMode toVkMipmapMode(EMipmapMode mode)
	{
		return (VkSamplerMipmapMode)0;
	}

	VkIndexType toVkIndexType(EIndexType type)
	{
		return (VkIndexType)0;
	}

	inline BufferCopyData VulkanInitBufferCopyData(uint32_t srcOffset, uint32_t dstOffset, uint32_t size)
	{
		BufferCopyData data;
		data.VkObject.srcOffset = srcOffset;
		data.VkObject.dstOffset = dstOffset;
		data.VkObject.size = size;
		return data;
	}

	inline BufferImageCopyData VulkanInitBufferImageCopyData(uint64_t srcOffset, uint32_t bufferRowLength, uint32_t bufferImageHeight, Offset imageOffset, Extent imageExtent, ImageSubresourceLayer subresource)
	{
		BufferImageCopyData data;
		data.VkObject.bufferOffset = srcOffset;
		data.VkObject.bufferRowLength = bufferRowLength;
		data.VkObject.bufferImageHeight = bufferImageHeight;
		data.VkObject.imageExtent = { imageExtent.X, imageExtent.Y, imageExtent.Z };
		data.VkObject.imageOffset = { imageOffset.X, imageOffset.Y, imageOffset.Z };
		data.VkObject.imageSubresource = subresource.VkObject;
		return data;
	}

	inline ImageSubresourceLayer VulkanInitImageSubresourceLayer(EImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t baseLayer, uint32_t layerCount)
	{
		ImageSubresourceLayer data;
		data.VkObject.aspectMask = toVkImageAspectFlags(aspectMask);
		data.VkObject.mipLevel = mipLevel;
		data.VkObject.baseArrayLayer = baseLayer;
		data.VkObject.layerCount = layerCount;
		return data;
	}

	inline ImageSubresourceRange VulkanInitImageSubresourceRange(EImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t levelCount, uint32_t baseLayer, uint32_t layerCount)
	{
		ImageSubresourceRange data;
		data.VkObject.aspectMask = toVkImageAspectFlags(aspectMask);
		data.VkObject.baseMipLevel = mipLevel;
		data.VkObject.levelCount = levelCount;
		data.VkObject.baseArrayLayer = baseLayer;
		data.VkObject.layerCount = layerCount;
		return data;
	}

	inline DescriptorPoolSize VulkanInitDescriptorPoolSize(EDescriptorType type, uint32_t count)
	{
		DescriptorPoolSize data;
		data.VkObject.type = toVkDescriptorType(type);
		data.VkObject.descriptorCount = count;
		return data;
	}

	inline DescriptorLayoutBinding VulkanInitDescriptorLayoutBinding(uint32_t binding, EDescriptorType type, uint32_t count, uint32_t shaderStageFlags)
	{
		DescriptorLayoutBinding data;
		data.VkObject.binding = binding;
		data.VkObject.descriptorType = toVkDescriptorType(type);
		data.VkObject.descriptorCount = count;
		data.VkObject.stageFlags = shaderStageFlags;
		data.VkObject.pImmutableSamplers = nullptr;
		return data;
	}

	inline DescriptorBufferInfo VulkanInitDescriptorBufferInfo(HBuffer buffer, uint64_t offset, uint64_t range)
	{
		DescriptorBufferInfo data;
		data.VkObject.buffer = buffer.VkHandle.Buffer;
		data.VkObject.offset = offset;
		data.VkObject.range = range;
		return data;
	}

	inline DescriptorImageInfo VulkanInitDescriptorImageInfo(HImageView imageView, HSampler sampler, EImageLayout imageLayout)
	{
		DescriptorImageInfo data;
		data.VkObject.imageView = imageView.VkHandle;
		data.VkObject.sampler = sampler.VkHandle;
		data.VkObject.imageLayout = toVkImageLayout(imageLayout);
		return data;
	}

	inline DescriptorWriteData VulkanInitDescriptorWriteData(HDescriptorSet dstSet, uint32_t binding, uint32_t index, EDescriptorType type, DescriptorImageInfo* imageInfo, DescriptorBufferInfo* bufferInfo, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(DescriptorImageInfo, VkDescriptorImageInfo);
		ASSERT_HANDLE_SIZE(DescriptorBufferInfo, VkDescriptorBufferInfo);
		VkDescriptorImageInfo* vulkanImageInfo = (VkDescriptorImageInfo*)imageInfo;
		VkDescriptorBufferInfo* vulkanBufferInfo = (VkDescriptorBufferInfo*)bufferInfo;

		DescriptorWriteData data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		data.VkObject.pNext = VK_NULL_HANDLE;
		data.VkObject.dstSet = dstSet.VkHandle;
		data.VkObject.dstBinding = binding;
		data.VkObject.dstArrayElement = index;
		data.VkObject.descriptorType = toVkDescriptorType(type);
		data.VkObject.descriptorCount = count;
		data.VkObject.pImageInfo = vulkanImageInfo;
		data.VkObject.pBufferInfo = vulkanBufferInfo;
		data.VkObject.pTexelBufferView = nullptr;
		return data;
	}

	inline RPAttachmentDescription VulkanInitRPAttachmentDescription(EFormat format, ESampleCountFlags sampleCount, ELoadOp lop, EStoreOp sop, ELoadOp stencilLop, EStoreOp stencilSop, EImageLayout initialLayout, EImageLayout finalLayout)
	{
		RPAttachmentDescription data;
		data.VkObject.flags = 0;
		data.VkObject.format = toVkFormat(format);
		data.VkObject.samples = (VkSampleCountFlagBits)toVkSampleCountFlags(sampleCount);
		data.VkObject.loadOp = toVkLoadOp(lop);
		data.VkObject.storeOp = toVkStoreOp(sop);
		data.VkObject.stencilLoadOp = toVkLoadOp(stencilLop);
		data.VkObject.stencilStoreOp = toVkStoreOp(stencilSop);
		data.VkObject.initialLayout = toVkImageLayout(initialLayout);
		data.VkObject.finalLayout = toVkImageLayout(finalLayout);
		return data;
	}

	inline RPAttachmentReference VulkanInitRPAttachmentReference(uint32_t attachment, EImageLayout layout)
	{
		RPAttachmentReference data; 
		data.VkObject.attachment = attachment;
		data.VkObject.layout = toVkImageLayout(layout);
		return data;
	}

	inline RPSubpassDescription VulkanInitRPSubpassDescription(EPipelineBindPoint bindPoint, RPAttachmentReference* inputs, uint32_t inputCount, RPAttachmentReference* colors, RPAttachmentReference* resolves, uint32_t colorCount, RPAttachmentReference* depthStencil, uint32_t* reserves, uint32_t reserveCount)
	{
		ASSERT_HANDLE_SIZE(RPAttachmentReference, VkAttachmentReference);
		VkAttachmentReference* vulkanInputs = (VkAttachmentReference*)inputs;
		VkAttachmentReference* vulkanColors = (VkAttachmentReference*)colors;
		VkAttachmentReference* vulkanResolves = (VkAttachmentReference*)resolves;
		VkAttachmentReference* vulkanDepthStencil = (VkAttachmentReference*)depthStencil;

		RPSubpassDescription data;
		data.VkObject.flags = 0;
		data.VkObject.pipelineBindPoint = toVkPipelineBindPoint(bindPoint);
		data.VkObject.inputAttachmentCount = inputCount;
		data.VkObject.pInputAttachments = vulkanInputs;
		data.VkObject.colorAttachmentCount = colorCount;
		data.VkObject.pColorAttachments = vulkanColors;
		data.VkObject.pResolveAttachments = vulkanResolves;
		data.VkObject.pDepthStencilAttachment = vulkanDepthStencil;
		data.VkObject.preserveAttachmentCount = reserveCount;
		data.VkObject.pPreserveAttachments = reserves;
		return data;
	}

	inline RPSubpassDependency VulkanInitRPSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass, EPipelineStageFlags srcStages, EPipelineStageFlags dstStages, EAccessFlags srcAccess, EAccessFlags dstAccess, EDependencyFlags dependencyFlags)
	{
		RPSubpassDependency data;
		data.VkObject.srcSubpass = srcSubpass;
		data.VkObject.dstSubpass = dstSubpass;
		data.VkObject.srcStageMask = toVkPipelineStages(srcStages);
		data.VkObject.dstStageMask = toVkPipelineStages(dstStages);
		data.VkObject.srcAccessMask = toVkAccessMask(srcAccess);
		data.VkObject.dstAccessMask = toVkAccessMask(dstAccess);
		data.VkObject.dependencyFlags = toVkDependencies(dependencyFlags);
		return data;
	}


	struct VulkanContext
	{
#ifdef _WIN32
		HMODULE VulkanDll;
#endif
		uint32_t VulkanVersion;

		VkInstance Instance = nullptr;
		VkDevice LogicalDevice;
		VkPhysicalDevice PhysicalDevice;
		VkPhysicalDeviceProperties DeviceProperties;
		VkDebugUtilsMessengerEXT DebugMessenger;

		VkQueue RenderQueue; uint32_t RenderQueueIndex;
		VkQueue TransferQueue; uint32_t TransferQueueIndex;

		VkQueueFamilyProperties* QueueFamilyProperties; uint32_t QueueFamilyCount;

		VmaAllocator MemoryAllocator;

		shaderc_compile_options_t CompilerOptions;

		//initialized by instance
		PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
		PFN_vkCreateInstance vkCreateInstance;
		PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
		PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
		PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;

		PFN_vkDestroyInstance vkDestroyInstance;
		PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
		PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
		PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
		PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
		PFN_vkCreateDevice vkCreateDevice;
		PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
		PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
		PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
		PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
		PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
		PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;

		//initialized by Device
		PFN_vkDestroyDevice vkDestroyDevice;
		PFN_vkGetDeviceQueue vkGetDeviceQueue;
		PFN_vkDestroyCommandPool vkDestroyCommandPool;
		PFN_vkResetCommandBuffer vkResetCommandBuffer;
		PFN_vkEndCommandBuffer vkEndCommandBuffer;
		PFN_vkCreateCommandPool vkCreateCommandPool;
		PFN_vkResetCommandPool vkResetCommandPool;
		PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
		PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
		PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
		PFN_vkQueueSubmit vkQueueSubmit;
		PFN_vkWaitForFences vkWaitForFences;
		PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
		PFN_vkCreateFramebuffer vkCreateFramebuffer;
		PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
		PFN_vkCreateImageView vkCreateImageView;
		PFN_vkDestroyImageView vkDestroyImageView;
		PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
		PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
		PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
		PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
		PFN_vkDestroyPipeline vkDestroyPipeline;
		PFN_vkCreateRenderPass vkCreateRenderPass;
		PFN_vkDestroyRenderPass vkDestroyRenderPass;
		PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
		PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
		PFN_vkDestroySemaphore vkDestroySemaphore;
		PFN_vkCreateSemaphore vkCreateSemaphore;
		PFN_vkGetFenceStatus vkGetFenceStatus;
		PFN_vkDestroyFence vkDestroyFence;
		PFN_vkCreateFence vkCreateFence;
		PFN_vkResetFences vkResetFences;
		PFN_vkQueuePresentKHR vkQueuePresentKHR;
		PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
		PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
		PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
		PFN_vkCreateImage vkCreateImage;
		PFN_vkMapMemory vkMapMemory;
		PFN_vkUnmapMemory vkUnmapMemory;
		PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
		PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
		PFN_vkCreateBuffer vkCreateBuffer;
		PFN_vkBindBufferMemory vkBindBufferMemory;
		PFN_vkDestroyBuffer vkDestroyBuffer;
		PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
		PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
		PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
		PFN_vkAllocateMemory vkAllocateMemory;
		PFN_vkFreeMemory vkFreeMemory;
		PFN_vkBindBufferMemory2 vkBindBufferMemory2;
		PFN_vkBindImageMemory2 vkBindImageMemory2;
		PFN_vkBindImageMemory vkBindImageMemory;
		PFN_vkDestroyImage vkDestroyImage;
		PFN_vkCmdSetViewport vkCmdSetViewport;
		PFN_vkCmdSetScissor vkCmdSetScissor;
		PFN_vkCmdBindPipeline vkCmdBindPipeline;
		PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
		PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
		PFN_vkCmdDraw vkCmdDraw;
		PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
		PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
		PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
		PFN_vkCreateShaderModule vkCreateShaderModule;
		PFN_vkDestroyShaderModule vkDestroyShaderModule;
		PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
		PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
		PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
		PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
		PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
		PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
		PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
		PFN_vkCreateSampler vkCreateSampler;
		PFN_vkDestroySampler vkDestroySampler;
		PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;

	} VkContext;


	VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: std::cerr << "VkError: " << pCallbackData->pMessage << '\n'; break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: std::cout << "VkWarning: " << pCallbackData->pMessage << '\n'; break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: std::cout << "VkInfo: " << pCallbackData->pMessage << '\n'; break;
		default: break; //std::cout << "VkVerbose: " << pCallbackData->pMessage << '\n'; break;
		}

		return VK_FALSE;
	}


	inline void VulkanInitialize(EAPI api)
	{
#ifdef _WIN32
		VkContext.VulkanDll = LoadLibrary(L"vulkan-1.dll");
		VkContext.vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(VkContext.VulkanDll, "vkGetInstanceProcAddr");
#endif
		INIT_INST_FUNC(vkCreateInstance);
		INIT_INST_FUNC(vkEnumerateInstanceVersion);
		INIT_INST_FUNC(vkEnumerateInstanceExtensionProperties);
		INIT_INST_FUNC(vkEnumerateInstanceLayerProperties);


		uint32_t layerCount = 0;
		const char* layers[10];

		uint32_t extensionCount = 1;
		const char* extensions[10] = { VK_KHR_SURFACE_EXTENSION_NAME };

#ifdef _DEBUG
		layers[layerCount++] = "VK_LAYER_KHRONOS_validation";
		extensions[extensionCount++] = { VK_KHR_SURFACE_EXTENSION_NAME };
		extensions[extensionCount++] = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };
		extensions[extensionCount++] = { VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME };
#endif

#ifdef _WIN32
		extensions[extensionCount++] = VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
#endif

		VkContext.vkEnumerateInstanceVersion(&VkContext.VulkanVersion);

		
		std::cout	<< VK_VERSION_MAJOR(VkContext.VulkanVersion) << "." 
					<< VK_VERSION_MINOR(VkContext.VulkanVersion) << "." 
					<< VK_VERSION_PATCH(VkContext.VulkanVersion) << "\n";

		//VkContext.VulkanVersion &= (~0xFFF); //remove patch version
			
		VkApplicationInfo appInfo;
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.pApplicationName = "Gravity: Control";
		appInfo.applicationVersion = 1;
		appInfo.pEngineName = "Gravity Engine";
		appInfo.engineVersion = 1;
		appInfo.apiVersion = VkContext.VulkanVersion;

		VkInstanceCreateInfo instInfo;
		instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instInfo.pNext = nullptr;
		instInfo.flags = 0;
		instInfo.pApplicationInfo = &appInfo;
		instInfo.enabledExtensionCount = extensionCount;
		instInfo.ppEnabledExtensionNames = extensions;
		instInfo.enabledLayerCount = layerCount;
		instInfo.ppEnabledLayerNames = layers;

#ifdef _DEBUG
		VkValidationFeatureEnableEXT enables[] = { VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT };
		VkValidationFeaturesEXT features;
		features.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
		features.pNext = nullptr;
		features.enabledValidationFeatureCount = 1;
		features.pEnabledValidationFeatures = enables;
		features.disabledValidationFeatureCount = 0;
		features.pDisabledValidationFeatures = nullptr;


		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.pNext = &features;
		debugCreateInfo.flags = 0;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = DebugCallback;
		debugCreateInfo.pUserData = nullptr;

		instInfo.pNext = &debugCreateInfo;
#endif

		VK_VALIDATE(VkContext.vkCreateInstance(&instInfo, nullptr, &VkContext.Instance))

		INIT_INST_FUNC(vkEnumeratePhysicalDevices);
		INIT_INST_FUNC(vkDestroyInstance);
		INIT_INST_FUNC(vkGetPhysicalDeviceQueueFamilyProperties);
		INIT_INST_FUNC(vkGetPhysicalDeviceFeatures);
		INIT_INST_FUNC(vkGetPhysicalDeviceProperties);
		INIT_INST_FUNC(vkCreateDevice);
		INIT_INST_FUNC(vkGetDeviceProcAddr);
		INIT_INST_FUNC(vkCreateDebugUtilsMessengerEXT);
		INIT_INST_FUNC(vkDestroyDebugUtilsMessengerEXT);
		INIT_INST_FUNC(vkCreateWin32SurfaceKHR);
		INIT_INST_FUNC(vkDestroySurfaceKHR);
		INIT_INST_FUNC(vkGetPhysicalDeviceSurfaceSupportKHR);
		INIT_INST_FUNC(vkGetPhysicalDeviceSurfaceFormatsKHR);
		INIT_INST_FUNC(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
		INIT_INST_FUNC(vkGetPhysicalDeviceSurfacePresentModesKHR);
		INIT_INST_FUNC(vkGetPhysicalDeviceMemoryProperties);
		INIT_INST_FUNC(vkGetPhysicalDeviceMemoryProperties2);

#ifdef _DEBUG
		VkDebugUtilsMessengerCreateInfoEXT createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = DebugCallback;
		createInfo.pUserData = nullptr;

		VK_VALIDATE(VkContext.vkCreateDebugUtilsMessengerEXT(VkContext.Instance, &createInfo, nullptr, &VkContext.DebugMessenger))
#endif


		uint32_t deviceCount;
		VK_VALIDATE(VkContext.vkEnumeratePhysicalDevices(VkContext.Instance, &deviceCount, nullptr))

		VkPhysicalDevice* GPUs = new VkPhysicalDevice[deviceCount];
		VK_VALIDATE(VkContext.vkEnumeratePhysicalDevices(VkContext.Instance, &deviceCount, GPUs))

		//TODO: choose good device
		VkContext.PhysicalDevice = GPUs[0];

		delete[] GPUs;


		VkContext.vkGetPhysicalDeviceQueueFamilyProperties(VkContext.PhysicalDevice, &VkContext.QueueFamilyCount, nullptr);

		VkDeviceQueueCreateInfo* queueInfo = new VkDeviceQueueCreateInfo[VkContext.QueueFamilyCount];
		VkContext.QueueFamilyProperties = new VkQueueFamilyProperties[VkContext.QueueFamilyCount];
		VkContext.vkGetPhysicalDeviceQueueFamilyProperties(VkContext.PhysicalDevice, &VkContext.QueueFamilyCount, VkContext.QueueFamilyProperties);

		VkPhysicalDeviceFeatures deviceFeatures;
		VkContext.vkGetPhysicalDeviceFeatures(VkContext.PhysicalDevice, &deviceFeatures);
		deviceFeatures.samplerAnisotropy = VK_TRUE;
		
		VkContext.vkGetPhysicalDeviceProperties(VkContext.PhysicalDevice, &VkContext.DeviceProperties);

		VkDeviceCreateInfo deviceInfo;
		const char* deviceExtensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		float queuePrios[] = { 1.f };

		for (size_t i = 0; i < VkContext.QueueFamilyCount; i++)
		{
			VkDeviceQueueCreateInfo newQueueInfo;
			newQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			newQueueInfo.pNext = nullptr;
			newQueueInfo.flags = 0;
			newQueueInfo.queueFamilyIndex = (uint32_t)i;
			newQueueInfo.queueCount = sizeof(queuePrios) / sizeof(*queuePrios); //We don't need more(probably)
			newQueueInfo.pQueuePriorities = queuePrios;

			queueInfo[i] = newQueueInfo;
		}

		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.pNext = nullptr;
		deviceInfo.flags = 0;
		deviceInfo.queueCreateInfoCount = VkContext.QueueFamilyCount;
		deviceInfo.pQueueCreateInfos = queueInfo;
		deviceInfo.enabledExtensionCount = sizeof(deviceExtensions) / sizeof(*deviceExtensions);
		deviceInfo.ppEnabledExtensionNames = deviceExtensions;
		deviceInfo.enabledLayerCount = 0;
		deviceInfo.ppEnabledLayerNames = nullptr;
		deviceInfo.pEnabledFeatures = &deviceFeatures;

		VK_VALIDATE(VkContext.vkCreateDevice(VkContext.PhysicalDevice, &deviceInfo, nullptr, &VkContext.LogicalDevice))

		delete[] queueInfo;

		INIT_DEV_FUNC(vkDestroyDevice);
		INIT_DEV_FUNC(vkGetDeviceQueue);
		INIT_DEV_FUNC(vkDestroyCommandPool);
		INIT_DEV_FUNC(vkResetCommandBuffer);
		INIT_DEV_FUNC(vkEndCommandBuffer);
		INIT_DEV_FUNC(vkCreateCommandPool);
		INIT_DEV_FUNC(vkResetCommandPool);
		INIT_DEV_FUNC(vkAllocateCommandBuffers);
		INIT_DEV_FUNC(vkCmdExecuteCommands);
		INIT_DEV_FUNC(vkBeginCommandBuffer);
		INIT_DEV_FUNC(vkQueueSubmit);
		INIT_DEV_FUNC(vkDestroyFramebuffer);
		INIT_DEV_FUNC(vkCreateFramebuffer);
		INIT_DEV_FUNC(vkCmdCopyBufferToImage);
		INIT_DEV_FUNC(vkCreateImageView);
		INIT_DEV_FUNC(vkDestroyImageView);
		INIT_DEV_FUNC(vkCmdCopyBuffer);
		INIT_DEV_FUNC(vkCreatePipelineLayout);
		INIT_DEV_FUNC(vkDestroyPipelineLayout);
		INIT_DEV_FUNC(vkCreateGraphicsPipelines);
		INIT_DEV_FUNC(vkDestroyPipeline);
		INIT_DEV_FUNC(vkCreateRenderPass);
		INIT_DEV_FUNC(vkDestroyRenderPass);
		INIT_DEV_FUNC(vkDestroySwapchainKHR);
		INIT_DEV_FUNC(vkCreateSwapchainKHR);
		INIT_DEV_FUNC(vkDestroySemaphore);
		INIT_DEV_FUNC(vkCreateSemaphore);
		INIT_DEV_FUNC(vkGetFenceStatus);
		INIT_DEV_FUNC(vkDestroyFence);
		INIT_DEV_FUNC(vkCreateFence);
		INIT_DEV_FUNC(vkResetFences);
		INIT_DEV_FUNC(vkQueuePresentKHR);
		INIT_DEV_FUNC(vkAcquireNextImageKHR);
		INIT_DEV_FUNC(vkGetSwapchainImagesKHR);
		INIT_DEV_FUNC(vkWaitForFences);
		INIT_DEV_FUNC(vkMapMemory);
		INIT_DEV_FUNC(vkUnmapMemory);
		INIT_DEV_FUNC(vkInvalidateMappedMemoryRanges);
		INIT_DEV_FUNC(vkFlushMappedMemoryRanges);
		INIT_DEV_FUNC(vkCreateBuffer);
		INIT_DEV_FUNC(vkBindBufferMemory);
		INIT_DEV_FUNC(vkDestroyBuffer);
		INIT_DEV_FUNC(vkGetBufferMemoryRequirements);
		INIT_DEV_FUNC(vkGetBufferMemoryRequirements2);
		INIT_DEV_FUNC(vkGetImageMemoryRequirements2);
		INIT_DEV_FUNC(vkAllocateMemory);
		INIT_DEV_FUNC(vkFreeMemory);
		INIT_DEV_FUNC(vkBindBufferMemory2);
		INIT_DEV_FUNC(vkBindImageMemory2);
		INIT_DEV_FUNC(vkBindImageMemory);
		INIT_DEV_FUNC(vkDestroyImage);
		INIT_DEV_FUNC(vkCreateImage);
		INIT_DEV_FUNC(vkGetImageMemoryRequirements);
		INIT_DEV_FUNC(vkCmdSetViewport);
		INIT_DEV_FUNC(vkCmdSetScissor);
		INIT_DEV_FUNC(vkCmdBindPipeline);
		INIT_DEV_FUNC(vkCmdBindVertexBuffers);
		INIT_DEV_FUNC(vkCmdBindIndexBuffer);
		INIT_DEV_FUNC(vkCmdDraw);
		INIT_DEV_FUNC(vkCmdDrawIndexed);
		INIT_DEV_FUNC(vkCmdBeginRenderPass);
		INIT_DEV_FUNC(vkCmdEndRenderPass);
		INIT_DEV_FUNC(vkCreateShaderModule);
		INIT_DEV_FUNC(vkDestroyShaderModule);
		INIT_DEV_FUNC(vkCreateDescriptorSetLayout);
		INIT_DEV_FUNC(vkDestroyDescriptorSetLayout);
		INIT_DEV_FUNC(vkUpdateDescriptorSets);
		INIT_DEV_FUNC(vkAllocateDescriptorSets);
		INIT_DEV_FUNC(vkCreateDescriptorPool);
		INIT_DEV_FUNC(vkDestroyDescriptorPool);
		INIT_DEV_FUNC(vkCmdBindDescriptorSets);
		INIT_DEV_FUNC(vkCreateSampler);
		INIT_DEV_FUNC(vkDestroySampler);
		INIT_DEV_FUNC(vkCmdPipelineBarrier);

		VmaVulkanFunctions vulkanFunctions;
		vulkanFunctions.vkGetPhysicalDeviceProperties = VkContext.vkGetPhysicalDeviceProperties;
		vulkanFunctions.vkGetPhysicalDeviceMemoryProperties = VkContext.vkGetPhysicalDeviceMemoryProperties;
		vulkanFunctions.vkAllocateMemory = VkContext.vkAllocateMemory;
		vulkanFunctions.vkFreeMemory = VkContext.vkFreeMemory;
		vulkanFunctions.vkMapMemory = VkContext.vkMapMemory;
		vulkanFunctions.vkUnmapMemory = VkContext.vkUnmapMemory;
		vulkanFunctions.vkFlushMappedMemoryRanges = VkContext.vkFlushMappedMemoryRanges;
		vulkanFunctions.vkInvalidateMappedMemoryRanges = VkContext.vkInvalidateMappedMemoryRanges;
		vulkanFunctions.vkBindBufferMemory = VkContext.vkBindBufferMemory;
		vulkanFunctions.vkBindImageMemory = VkContext.vkBindImageMemory;
		vulkanFunctions.vkGetBufferMemoryRequirements = VkContext.vkGetBufferMemoryRequirements;
		vulkanFunctions.vkGetImageMemoryRequirements = VkContext.vkGetImageMemoryRequirements;
		vulkanFunctions.vkCreateBuffer = VkContext.vkCreateBuffer;
		vulkanFunctions.vkDestroyBuffer = VkContext.vkDestroyBuffer;
		vulkanFunctions.vkCreateImage = VkContext.vkCreateImage;
		vulkanFunctions.vkDestroyImage = VkContext.vkDestroyImage;
		vulkanFunctions.vkCmdCopyBuffer = VkContext.vkCmdCopyBuffer;
		vulkanFunctions.vkGetBufferMemoryRequirements2KHR = VkContext.vkGetBufferMemoryRequirements2;
		vulkanFunctions.vkGetImageMemoryRequirements2KHR = VkContext.vkGetImageMemoryRequirements2;
		vulkanFunctions.vkBindBufferMemory2KHR = VkContext.vkBindBufferMemory2;
		vulkanFunctions.vkBindImageMemory2KHR = VkContext.vkBindImageMemory2;
		vulkanFunctions.vkGetPhysicalDeviceMemoryProperties2KHR = VkContext.vkGetPhysicalDeviceMemoryProperties2;

		VmaAllocatorCreateInfo allocCreateInfo;
		allocCreateInfo.device = VkContext.LogicalDevice;
		allocCreateInfo.physicalDevice = VkContext.PhysicalDevice;
		allocCreateInfo.instance = VkContext.Instance;
		allocCreateInfo.vulkanApiVersion = VkContext.VulkanVersion;
		allocCreateInfo.pVulkanFunctions = &vulkanFunctions;
		allocCreateInfo.pTypeExternalMemoryHandleTypes = nullptr;
		allocCreateInfo.pAllocationCallbacks = nullptr;
		allocCreateInfo.pDeviceMemoryCallbacks = nullptr;
		allocCreateInfo.pHeapSizeLimit = nullptr;
		allocCreateInfo.preferredLargeHeapBlockSize = 0;

		VK_VALIDATE(vmaCreateAllocator(&allocCreateInfo, &VkContext.MemoryAllocator))

		VkContext.RenderQueueIndex = 0;
		for (uint32_t it = 0; it < VkContext.QueueFamilyCount; it++) {
			if (((VkContext.QueueFamilyProperties[it].queueFlags & VK_QUEUE_GRAPHICS_BIT) && VkContext.QueueFamilyProperties[it].queueCount > VkContext.QueueFamilyProperties[VkContext.RenderQueueIndex].queueCount)
				|| !(VkContext.QueueFamilyProperties[VkContext.RenderQueueIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
				VkContext.RenderQueueIndex = it;
			}
		}

		VkContext.vkGetDeviceQueue(VkContext.LogicalDevice, VkContext.RenderQueueIndex, 0, &VkContext.RenderQueue);


		VkContext.TransferQueueIndex = 0;
		for (uint32_t it = 0; it < VkContext.QueueFamilyCount; it++) {
			if ((VkContext.QueueFamilyProperties[it].queueFlags & VK_QUEUE_TRANSFER_BIT) && it != VkContext.RenderQueueIndex) {
				VkContext.TransferQueueIndex = it;
				break;
			}
			else if (VkContext.QueueFamilyProperties[it].queueFlags & VK_QUEUE_TRANSFER_BIT) {
				VkContext.TransferQueueIndex = it;
			}
		}

		VkContext.vkGetDeviceQueue(VkContext.LogicalDevice, VkContext.TransferQueueIndex, 0, &VkContext.TransferQueue);
	}

	inline void VulkanTerminate()
	{
		delete[] VkContext.QueueFamilyProperties;

		vmaDestroyAllocator(VkContext.MemoryAllocator);
		VkContext.vkDestroyDevice(VkContext.LogicalDevice, nullptr);
#ifdef _DEBUG
		VkContext.vkDestroyDebugUtilsMessengerEXT(VkContext.Instance, VkContext.DebugMessenger, nullptr);
#endif
		VkContext.vkDestroyInstance(VkContext.Instance, nullptr);
	}

	inline void VulkanGetDeviceQueueu(HQueue& handle, uint32_t queueFamily, uint32_t queueIndex)
	{
		VkContext.vkGetDeviceQueue(VkContext.LogicalDevice, queueFamily, queueIndex, &handle.VkHandle);
	}

	inline void VulkanCreateBuffer(HBuffer& handle, uint32_t size, EBufferUsage bufferUsage, EMemoryUsage memoryUsage)
	{
		VkBufferCreateInfo bufferInfo;
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.pNext = nullptr;
		bufferInfo.flags = 0;
		bufferInfo.size = size;
		bufferInfo.usage = toVkBufferUsage(bufferUsage);
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bufferInfo.queueFamilyIndexCount = 0;
		bufferInfo.pQueueFamilyIndices = nullptr;

		VmaAllocationCreateInfo allocInfo;
		allocInfo.flags = 0;
		allocInfo.memoryTypeBits = 0;
		allocInfo.requiredFlags = 0;
		allocInfo.preferredFlags = 0;
		allocInfo.pool = nullptr;
		allocInfo.pUserData = nullptr;
		allocInfo.usage = toVkMemoryUsage(memoryUsage);

		VK_VALIDATE(vmaCreateBuffer(VkContext.MemoryAllocator, &bufferInfo, &allocInfo, &handle.VkHandle.Buffer, &handle.VkHandle.Allocation, nullptr))
	}

	inline void VulkanDestroyBuffer(HBuffer handle)
	{
		vmaDestroyBuffer(VkContext.MemoryAllocator, handle.VkHandle.Buffer, handle.VkHandle.Allocation);
	}

	inline void VulkanUploadMemory(HBuffer dstBuffer, MemoryCopyData* copyData, uint32_t count)
	{
		void* deviceMemory;
		VK_VALIDATE(vmaMapMemory(VkContext.MemoryAllocator, dstBuffer.VkHandle.Allocation, &deviceMemory))
		for (uint32_t i = 0; i < count; i++) {
			memcpy((char*)deviceMemory + copyData[i].DstOffset, copyData[i].Data, copyData[i].Size);
		}
		vmaUnmapMemory(VkContext.MemoryAllocator, dstBuffer.VkHandle.Allocation);
	}

	inline void VulkanCreateImage(HImage& handle, uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevels, uint32_t layers, 
		EFormat format, EImageLayout initialLayout, EImageType type, EImageUsageFlags usage, ESampleCountFlags sampleCount, EImageTiling tiling)
	{
		VkImageCreateInfo imageCreateInfo;
		imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageCreateInfo.pNext = nullptr;
		imageCreateInfo.flags = 0;
		imageCreateInfo.extent = { width, height, depth };
		imageCreateInfo.mipLevels = mipLevels;
		imageCreateInfo.arrayLayers = layers;
		imageCreateInfo.imageType = toVkimageType(type);
		imageCreateInfo.initialLayout = toVkImageLayout(initialLayout);
		imageCreateInfo.samples = (VkSampleCountFlagBits)toVkSampleCountFlags(sampleCount);
		imageCreateInfo.format = toVkFormat(format);
		imageCreateInfo.tiling = toVkImageTiling(tiling);
		imageCreateInfo.usage = toVkImageUsageFlags(usage);
		imageCreateInfo.queueFamilyIndexCount = 0;
		imageCreateInfo.pQueueFamilyIndices = nullptr;
		imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VmaAllocationCreateInfo allocInfo;
		allocInfo.flags = 0;
		allocInfo.memoryTypeBits = 0;
		allocInfo.requiredFlags = 0;
		allocInfo.preferredFlags = 0;
		allocInfo.pool = nullptr;
		allocInfo.pUserData = nullptr;
		allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

		VK_VALIDATE(vmaCreateImage(VkContext.MemoryAllocator, &imageCreateInfo, &allocInfo, &handle.VkHandle.Image, &handle.VkHandle.Allocation, nullptr))
	}

	inline void VulkanDestroyImage(HImage handle)
	{
		vmaDestroyImage(VkContext.MemoryAllocator, handle.VkHandle.Image, handle.VkHandle.Allocation);
	}

	inline void VulkanCreateImageView(HImageView& handle, HImage image, EFormat format, EImageViewType type, ImageSubresourceRange subresource)
	{
		VkImageViewCreateInfo viewInfo;
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.pNext = nullptr;
		viewInfo.flags = 0;
		viewInfo.image = image.VkHandle.Image;
		viewInfo.format = toVkFormat(format);
		viewInfo.viewType = toVkImageViewType(type);
		viewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
		viewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
		viewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
		viewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
		viewInfo.subresourceRange = subresource.VkObject;

		VK_VALIDATE(VkContext.vkCreateImageView(VkContext.LogicalDevice, &viewInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyImageView(HImageView handle)
	{
		VkContext.vkDestroyImageView(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateCmdPool(HCmdPool& handle, uint32_t queueIndex)
	{
		VkCommandPoolCreateInfo createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.queueFamilyIndex = queueIndex;
		createInfo.flags = 0;

		VK_VALIDATE(VkContext.vkCreateCommandPool(VkContext.LogicalDevice, &createInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyCmdPool(HCmdPool handle)
	{
		VkContext.vkDestroyCommandPool(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanResetCmdPool(HCmdPool handle)
	{
		VK_VALIDATE(VkContext.vkResetCommandPool(VkContext.LogicalDevice, handle.VkHandle, 0))
	}

	inline void VulkanCreateCmdLists(HCmdList* cmdLists, uint32_t count, HCmdPool parentPool, ECmdListLevel listLevel)
	{
		ASSERT_HANDLE_SIZE(HCmdList, VkCommandBuffer);
		VkCommandBuffer* vulkanCmdLists = (VkCommandBuffer*)cmdLists;

		VkCommandBufferAllocateInfo allocInfo;
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.pNext = nullptr;
		allocInfo.commandPool = parentPool.VkHandle;
		allocInfo.commandBufferCount = count;
		allocInfo.level = toVkCmdListLevel(listLevel);

		VK_VALIDATE(VkContext.vkAllocateCommandBuffers(VkContext.LogicalDevice, &allocInfo, vulkanCmdLists))
	}

	inline void VulkanBeginRecording(HCmdList cmdList, HRenderPass renderPass, uint32_t subpass, HFramebuffer framebuffer, EBeginRecordingFlags flags)
	{
		VkCommandBufferInheritanceInfo inheritanceInfo;
		inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
		inheritanceInfo.pNext = nullptr;
		inheritanceInfo.occlusionQueryEnable = false;
		inheritanceInfo.queryFlags = 0;
		inheritanceInfo.pipelineStatistics = 0;
		inheritanceInfo.framebuffer = framebuffer.VkHandle;
		inheritanceInfo.renderPass = renderPass.VkHandle;
		inheritanceInfo.subpass = subpass;

		VkCommandBufferBeginInfo beginInfo;
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pNext = nullptr;
		beginInfo.flags = toVkBeginRecordingFlags(flags);
		beginInfo.pInheritanceInfo = &inheritanceInfo;

		VK_VALIDATE(VkContext.vkBeginCommandBuffer(cmdList.VkHandle, &beginInfo))
	}

	inline void VulkanStopRecording(HCmdList cmdList)
	{
		VK_VALIDATE(VkContext.vkEndCommandBuffer(cmdList.VkHandle))
	}

	inline void VulkanSubmitCmdLists(HQueue queue, HCmdList* lists, EPipelineStageFlags* stageFlags, uint32_t count, HSemaphore* signalSemaphores, uint32_t signalCount, HSemaphore* waitSemaphores, uint32_t waitCount)
	{
		ASSERT_HANDLE_SIZE(HCmdList, VkCommandBuffer);
		ASSERT_HANDLE_SIZE(HSemaphore, VkSemaphore);
		ASSERT_HANDLE_SIZE(EPipelineStageFlags, VkPipelineStageFlags);
		VkCommandBuffer* vulkanCmdLists = (VkCommandBuffer*)lists;
		VkSemaphore* vulkanSignalSemaphores = (VkSemaphore*)signalSemaphores;
		VkSemaphore* vulkanWaitSemaphores = (VkSemaphore*)waitSemaphores;
		VkPipelineStageFlags* vulkanStageFlags = (VkPipelineStageFlags*)stageFlags;

		VkSubmitInfo submitInfo;
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;
		submitInfo.pWaitDstStageMask = vulkanStageFlags;
		submitInfo.waitSemaphoreCount = waitCount;
		submitInfo.pWaitSemaphores = vulkanWaitSemaphores;
		submitInfo.commandBufferCount = count;
		submitInfo.pCommandBuffers = vulkanCmdLists;
		submitInfo.signalSemaphoreCount = signalCount;
		submitInfo.pSignalSemaphores = vulkanSignalSemaphores;

		VK_VALIDATE(VkContext.vkQueueSubmit(queue.VkHandle, 1, &submitInfo, NULL))
	}

	inline void VulkanResetCmdList(HCmdList cmdList, bool releaseResources)
	{
		VK_VALIDATE(VkContext.vkResetCommandBuffer(cmdList.VkHandle, releaseResources))
	}

	inline void VulkanCreateDescriptorPool(HDescriptorPool& handle, DescriptorPoolSize* poolSizes, uint32_t poolCount, uint32_t maxSets)
	{
		ASSERT_HANDLE_SIZE(DescriptorPoolSize, VkDescriptorPoolSize);
		VkDescriptorPoolSize* vulkanPoolSizes = (VkDescriptorPoolSize*)poolSizes;

		VkDescriptorPoolCreateInfo poolInfo;
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.pNext = VK_NULL_HANDLE;
		poolInfo.flags = 0;
		poolInfo.poolSizeCount = poolCount;
		poolInfo.pPoolSizes = vulkanPoolSizes;
		poolInfo.maxSets = maxSets;

		VK_VALIDATE(VkContext.vkCreateDescriptorPool(VkContext.LogicalDevice, &poolInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyDescriptorPool(HDescriptorPool handle)
	{
		VkContext.vkDestroyDescriptorPool(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateDescriptorLayout(HDescriptorLayout& handle, DescriptorLayoutBinding* bindings, uint32_t bindingCount)
	{
		ASSERT_HANDLE_SIZE(DescriptorLayoutBinding, VkDescriptorSetLayoutBinding);
		VkDescriptorSetLayoutBinding* vulkanBindings = (VkDescriptorSetLayoutBinding*)bindings;

		VkDescriptorSetLayoutCreateInfo layoutInfo;
		layoutInfo.pNext = VK_NULL_HANDLE;
		layoutInfo.flags = 0;
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = bindingCount;
		layoutInfo.pBindings = vulkanBindings;

		VK_VALIDATE(VkContext.vkCreateDescriptorSetLayout(VkContext.LogicalDevice, &layoutInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyDescriptorLayout(HDescriptorLayout handle)
	{
		VkContext.vkDestroyDescriptorSetLayout(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateDescriptorSets(HDescriptorSet* handles, HDescriptorLayout* layouts, uint32_t count, HDescriptorPool parentPool)
	{
		ASSERT_HANDLE_SIZE(HDescriptorSet, VkDescriptorSet);
		ASSERT_HANDLE_SIZE(HDescriptorLayout, VkDescriptorSetLayout);
		VkDescriptorSet* vulkanHandles = (VkDescriptorSet*)handles;
		VkDescriptorSetLayout* vulkanLayouts = (VkDescriptorSetLayout*)layouts;

		VkDescriptorSetAllocateInfo allocInfo;
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = parentPool.VkHandle;
		allocInfo.pSetLayouts = vulkanLayouts;
		allocInfo.descriptorSetCount = count;

		VK_VALIDATE(VkContext.vkAllocateDescriptorSets(VkContext.LogicalDevice, &allocInfo, vulkanHandles))
	}

	inline void VulkanWriteDescriptorSet(DescriptorWriteData* writes, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(DescriptorWriteData, VkWriteDescriptorSet);
		VkWriteDescriptorSet* vulkanWrites = (VkWriteDescriptorSet*)writes;

		VkContext.vkUpdateDescriptorSets(VkContext.LogicalDevice, count, vulkanWrites, 0, nullptr);
	}

	inline void VulkanCreateFramebuffer(HFramebuffer& handle, HRenderPass renderPass, HImageView* attachments, uint32_t attachmentCount, uint32_t width, uint32_t height, uint32_t layers)
	{
		ASSERT_HANDLE_SIZE(HImageView, VkImageView);
		VkImageView* vulkanAttachments = (VkImageView*)attachments;

		VkFramebufferCreateInfo frameBufferInfo;
		frameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		frameBufferInfo.pNext = nullptr;
		frameBufferInfo.renderPass = renderPass.VkHandle;
		frameBufferInfo.attachmentCount = attachmentCount;
		frameBufferInfo.pAttachments = vulkanAttachments;
		frameBufferInfo.width = width;
		frameBufferInfo.height = height;
		frameBufferInfo.layers = layers;

		VK_VALIDATE(VkContext.vkCreateFramebuffer(VkContext.LogicalDevice, &frameBufferInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyFramebuffer(HFramebuffer handle)
	{
		VkContext.vkDestroyFramebuffer(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateRenderPass(HRenderPass& handle, RPAttachmentDescription* attachments, uint32_t attachmentCount, RPSubpassDescription* subpasses, uint32_t subpassCount, RPSubpassDependency* dependencies, uint32_t dependencyCount)
	{
		ASSERT_HANDLE_SIZE(RPAttachmentDescription, VkAttachmentDescription);
		ASSERT_HANDLE_SIZE(RPSubpassDescription, VkSubpassDescription);
		ASSERT_HANDLE_SIZE(RPSubpassDependency, VkSubpassDependency);
		VkAttachmentDescription* vulkanAttachments = (VkAttachmentDescription*)attachments;
		VkSubpassDescription* vulkanSubpasses = (VkSubpassDescription*)subpasses;
		VkSubpassDependency* vulkanDependencies = (VkSubpassDependency*)dependencies;

		VkRenderPassCreateInfo renderPassInfo;
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.pNext = nullptr;
		renderPassInfo.attachmentCount = attachmentCount;
		renderPassInfo.pAttachments = vulkanAttachments;
		renderPassInfo.subpassCount = subpassCount;
		renderPassInfo.pSubpasses = vulkanSubpasses;
		renderPassInfo.dependencyCount = dependencyCount;
		renderPassInfo.pDependencies = vulkanDependencies;

		VK_VALIDATE(VkContext.vkCreateRenderPass(VkContext.LogicalDevice, &renderPassInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyRenderPass(HRenderPass handle)
	{
		VkContext.vkDestroyRenderPass(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateShaderCompiler(HShaderCompiler& handle)
	{
		handle.VkHandle = shaderc_compiler_initialize();
		VkContext.CompilerOptions = shaderc_compile_options_initialize();
		shaderc_compile_options_set_source_language(VkContext.CompilerOptions, shaderc_source_language_glsl);
		shaderc_compile_options_set_optimization_level(VkContext.CompilerOptions, shaderc_optimization_level_performance);
	}

	inline void VulkanDestroyShaderCompiler(HShaderCompiler handle)
	{
		shaderc_compile_options_release(VkContext.CompilerOptions);
		shaderc_compiler_release(handle.VkHandle);
	}

	inline void VulkanCreateShader(HShader& handle, HShaderCompiler compiler, EShaderStageFlags stage, const char* code, uint32_t size)
	{
		shaderc_compilation_result_t result = shaderc_compile_into_spv(compiler.VkHandle, code, size,
												toShadercShaderKind(stage), "File", "main", VkContext.CompilerOptions);

		if (shaderc_result_get_compilation_status(result) != shaderc_compilation_status_success) {
			std::cout << shaderc_result_get_error_message(result) << "\n";
			verify(false, "Shader compilation failed.")
		}

		VkPipelineShaderStageCreateInfo shaderStageCreateInfo;
		shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStageCreateInfo.pNext = nullptr;
		shaderStageCreateInfo.pSpecializationInfo = nullptr;
		shaderStageCreateInfo.flags = 0;
		shaderStageCreateInfo.stage = (VkShaderStageFlagBits)toVkShaderStageFlags(stage);
		shaderStageCreateInfo.pName = "main";

		VkShaderModuleCreateInfo moduleCreateInfo;
		moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		moduleCreateInfo.pNext = nullptr;
		moduleCreateInfo.flags = 0;
		moduleCreateInfo.codeSize = shaderc_result_get_length(result);
		moduleCreateInfo.pCode = (uint32_t*)shaderc_result_get_bytes(result);

		VK_VALIDATE(VkContext.vkCreateShaderModule(VkContext.LogicalDevice, &moduleCreateInfo, nullptr, &handle.VkHandle))

		shaderc_result_release(result);
	}

	inline void VulkanDestroyShader(HShader handle)
	{
		VkContext.vkDestroyShaderModule(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateSampler(HSampler& handle, EFilter magFilter, EFilter minFilter, EAddressMode addressMode, EMipmapMode mipMode, float minLod, float maxLod, float lodBias, bool anisotropy, float maxAnisotropy, bool compare, ECompareOp op)
	{
		VkSamplerCreateInfo samplerInfo;
		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerInfo.pNext = VK_NULL_HANDLE;
		samplerInfo.flags = 0;
		samplerInfo.magFilter = toVkFilter(magFilter);
		samplerInfo.minFilter = toVkFilter(minFilter);
		samplerInfo.addressModeU = toVkAddressMode(addressMode);
		samplerInfo.addressModeV = toVkAddressMode(addressMode);
		samplerInfo.addressModeW = toVkAddressMode(addressMode);
		samplerInfo.anisotropyEnable = anisotropy;
		samplerInfo.maxAnisotropy = (maxAnisotropy > VkContext.DeviceProperties.limits.maxSamplerAnisotropy ? VkContext.DeviceProperties.limits.maxSamplerAnisotropy : maxAnisotropy);
		samplerInfo.compareEnable = compare;
		samplerInfo.compareOp = toVkCompareOp(op);
		samplerInfo.mipmapMode = toVkMipmapMode(mipMode);
		samplerInfo.mipLodBias = lodBias;
		samplerInfo.minLod = minLod;
		samplerInfo.maxLod = maxLod;
		samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;

		VK_VALIDATE(VkContext.vkCreateSampler(VkContext.LogicalDevice, &samplerInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroySampler(HSampler handle)
	{
		VkContext.vkDestroySampler(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateSemaphore(HSemaphore& handle, uint64_t initialValue)
	{
		VkSemaphoreTypeCreateInfo semaphoreType;
		semaphoreType.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
		semaphoreType.pNext = nullptr;
		semaphoreType.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE;
		semaphoreType.initialValue = initialValue;

		VkSemaphoreCreateInfo semaphoreCreateInfo;
		semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphoreCreateInfo.pNext = &semaphoreType;
		semaphoreCreateInfo.flags = 0;

		VK_VALIDATE(VkContext.vkCreateSemaphore(VkContext.LogicalDevice, &semaphoreCreateInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroySemaphore(HSemaphore handle)	
	{
		VkContext.vkDestroySemaphore(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateSurface(HSurface& handle, void* window, void* module, void* monitor)
	{
		VkWin32SurfaceCreateInfoKHR SurfaceInfo;
		SurfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		SurfaceInfo.pNext = nullptr;
		SurfaceInfo.hinstance = (HINSTANCE)module;
		SurfaceInfo.hwnd = (HWND)window;

		VK_VALIDATE(VkContext.vkCreateWin32SurfaceKHR(VkContext.Instance, &SurfaceInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroySurface(HSurface handle)
	{
		VkContext.vkDestroySurfaceKHR(VkContext.Instance, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateSwapchain(HSwapchain& handle, HSwapchain old, HSurface surface, HQueue* presentQueue, uint32_t* layers, uint32_t* imageCount, uint32_t* width, uint32_t* height)
	{
		VkSwapchainCreateInfoKHR swapchainInfo;

		uint32_t formatCount;
		VK_VALIDATE(VkContext.vkGetPhysicalDeviceSurfaceFormatsKHR(VkContext.PhysicalDevice, surface.VkHandle, &formatCount, nullptr))

		VkSurfaceFormatKHR* surfaceFormats = new VkSurfaceFormatKHR[formatCount];
		VK_VALIDATE(VkContext.vkGetPhysicalDeviceSurfaceFormatsKHR(VkContext.PhysicalDevice, surface.VkHandle, &formatCount, surfaceFormats))

		if (surfaceFormats[0].format == VK_FORMAT_UNDEFINED) {
			swapchainInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
			swapchainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		}
		else {
			swapchainInfo.imageFormat = surfaceFormats[0].format;
			swapchainInfo.imageColorSpace = surfaceFormats[0].colorSpace;
		}

		delete[] surfaceFormats;

		uint32_t presentModeCount;
		VK_VALIDATE(VkContext.vkGetPhysicalDeviceSurfacePresentModesKHR(VkContext.PhysicalDevice, surface.VkHandle, &presentModeCount, nullptr))

		VkPresentModeKHR presentModes[6];
		VK_VALIDATE(VkContext.vkGetPhysicalDeviceSurfacePresentModesKHR(VkContext.PhysicalDevice, surface.VkHandle, &presentModeCount, presentModes))

		VkPresentModeKHR presentModeOrder[6] = { 
			VK_PRESENT_MODE_MAILBOX_KHR, 
			VK_PRESENT_MODE_IMMEDIATE_KHR,
			VK_PRESENT_MODE_FIFO_KHR, 
			VK_PRESENT_MODE_FIFO_RELAXED_KHR, 
			VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR,
			VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR 
		};

		for (uint32_t x = 5; x >= 0; x--) {
			for (uint32_t y = 0; y < presentModeCount; y++) {
				if (presentModeOrder[x] == presentModes[y]) {
					swapchainInfo.presentMode = presentModes[y];
				}
			}
		}

		VkSurfaceCapabilitiesKHR capabilities;
		VK_VALIDATE(VkContext.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkContext.PhysicalDevice, surface.VkHandle, &capabilities))

		VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] = {
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
			VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR
		};

		for (uint32_t i = 3; i >= 0; i--) {
			if (capabilities.supportedCompositeAlpha & compositeAlphaFlags[i]) {
				swapchainInfo.compositeAlpha = compositeAlphaFlags[i];
			}
		}

		if (*imageCount > capabilities.maxImageCount && capabilities.maxImageCount != 0) {
			*imageCount = capabilities.maxImageCount;
		}
		else if (*imageCount < capabilities.minImageCount && capabilities.maxImageCount != 0) {
			*imageCount = capabilities.minImageCount;
		}

		if (*layers > capabilities.maxImageArrayLayers) {
			*layers = capabilities.maxImageArrayLayers;
		}

		if (capabilities.currentExtent.height == 0xFFFFFFFF) {
			if (*height > capabilities.maxImageExtent.height) {
				*height = capabilities.maxImageExtent.height;
			}
			else if (*height < capabilities.minImageExtent.height) {
				*height = capabilities.minImageExtent.height;
			}
		}
		else {
			*height = capabilities.currentExtent.height;
		}

		if (capabilities.currentExtent.width == 0xFFFFFFFF) {
			if (*width > capabilities.maxImageExtent.width) {
				*width = capabilities.maxImageExtent.width;
			}
			else if (*width < capabilities.minImageExtent.width) {
				*width = capabilities.minImageExtent.width;
			}
		}
		else {
			*width = capabilities.currentExtent.width;
		}


		uint32_t presentQueueIndex = 0;
		for (uint32_t it = 0; it < VkContext.QueueFamilyCount; it++) {
			VkBool32 presentSupport = false;
			VK_VALIDATE(VkContext.vkGetPhysicalDeviceSurfaceSupportKHR(VkContext.PhysicalDevice, it, surface.VkHandle, &presentSupport))
			if (presentSupport) {
				presentQueueIndex = it;
			}
			if (presentSupport && it == VkContext.RenderQueueIndex) {
				presentQueueIndex = it;
				break;
			}
		}

		VkContext.vkGetDeviceQueue(VkContext.LogicalDevice, presentQueueIndex, 0, &presentQueue->VkHandle);

		
		swapchainInfo.queueFamilyIndexCount = 0;
		swapchainInfo.pQueueFamilyIndices = nullptr;

		uint32_t indices[2] = { presentQueueIndex, VkContext.RenderQueueIndex };
		if (presentQueueIndex != VkContext.RenderQueueIndex) {
			swapchainInfo.queueFamilyIndexCount = sizeof(indices) / sizeof(*indices);
			swapchainInfo.pQueueFamilyIndices = indices;
		}


		swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainInfo.pNext = nullptr;
		swapchainInfo.surface = surface.VkHandle;
		swapchainInfo.minImageCount = *imageCount;
		swapchainInfo.imageExtent.width = *width;
		swapchainInfo.imageExtent.height = *height;
		swapchainInfo.preTransform = capabilities.currentTransform;
		swapchainInfo.imageArrayLayers = *layers;
		swapchainInfo.oldSwapchain = old.VkHandle;
		swapchainInfo.clipped = true;
		swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VK_VALIDATE(VkContext.vkCreateSwapchainKHR(VkContext.LogicalDevice, &swapchainInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroySwapchain(HSwapchain handle)
	{
		VkContext.vkDestroySwapchainKHR(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanGetSwapchainImages(HImage* images, HSwapchain swapchain)
	{
		uint32_t imageCount;
		VK_VALIDATE(VkContext.vkGetSwapchainImagesKHR(VkContext.LogicalDevice, swapchain.VkHandle, &imageCount, nullptr))

		VkImage* swapchainImages = new VkImage[imageCount];
		VK_VALIDATE(VkContext.vkGetSwapchainImagesKHR(VkContext.LogicalDevice, swapchain.VkHandle, &imageCount, swapchainImages))

		for (uint32_t i = 0; i < imageCount; i++) {
			images[i].VkHandle.Image = swapchainImages[i];
		}
		
		delete[] swapchainImages;
	}

	inline void VulkanCreateGraphicsPipelines(HPipeline* handles, GraphicsPipelineCreateInfo* createInfos, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(VkGraphicsPipelineCreateInfo, GraphicsPipelineCreateInfo);
		ASSERT_HANDLE_SIZE(HPipeline, VkPipeline);
		VkGraphicsPipelineCreateInfo* vulkanCreateInfos = (VkGraphicsPipelineCreateInfo*)createInfos;
		VkPipeline* vulkanHandles = (VkPipeline*)handles;

		VK_VALIDATE(VkContext.vkCreateGraphicsPipelines(VkContext.LogicalDevice, VK_NULL_HANDLE, count, vulkanCreateInfos, nullptr, vulkanHandles))
	}

	inline void VulkanDestroyPipeline(HPipeline handle)
	{
		VkContext.vkDestroyPipeline(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreatePipelineLayout(HPipelineLayout& handle, PipelineLayoutCreateInfo createInfo)
	{
		VK_VALIDATE(VkContext.vkCreatePipelineLayout(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyPipelineLayout(HPipelineLayout handle)
	{
		VkContext.vkDestroyPipelineLayout(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCopyBuffer(HCmdList cmdList, HBuffer srcBuffer, HBuffer dstBuffer, BufferCopyData* copyData, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(BufferCopyData, VkBufferCopy);
		VkBufferCopy* vulkanCopyData = (VkBufferCopy*)copyData;

		VkContext.vkCmdCopyBuffer(cmdList.VkHandle, srcBuffer.VkHandle.Buffer, dstBuffer.VkHandle.Buffer, count, vulkanCopyData);
	}

	inline void VulkanCopyBufferToImage(HCmdList cmdList, HBuffer srcBuffer, HImage dstImage, EImageLayout currentLayout, BufferImageCopyData* copyData, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(BufferImageCopyData, VkBufferImageCopy);
		VkBufferImageCopy* vulkanCopyData = (VkBufferImageCopy*)copyData;

		VkContext.vkCmdCopyBufferToImage(cmdList.VkHandle, srcBuffer.VkHandle.Buffer, dstImage.VkHandle.Image, toVkImageLayout(currentLayout), count, vulkanCopyData);
	}

	inline void VulkanExecuteCmdLists(HCmdList cmdList, HCmdList* cmdLists, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(HCmdList, VkCommandBuffer);
		VkCommandBuffer* vulkanCmdLists = (VkCommandBuffer*)cmdLists;

		VkContext.vkCmdExecuteCommands(cmdList.VkHandle, count, vulkanCmdLists);
	}

	inline void VulkanBeginRenderPass(HCmdList cmdList, HRenderPass renderPass, HFramebuffer framebuffer, Scissor scissor, ClearValue* clearValues, uint32_t clearValueCount, bool inlineCommands)
	{
		ASSERT_HANDLE_SIZE(ClearValue, VkClearValue);
		VkClearValue* vulkanClearValues = (VkClearValue*)clearValues;
		
		VkRenderPassBeginInfo rpBeginInfo;
		rpBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		rpBeginInfo.pNext = nullptr;
		rpBeginInfo.framebuffer = framebuffer.VkHandle;
		rpBeginInfo.renderPass = renderPass.VkHandle;
		rpBeginInfo.renderArea = scissor.VkObject;
		rpBeginInfo.clearValueCount = clearValueCount;
		rpBeginInfo.pClearValues = vulkanClearValues;

		VkContext.vkCmdBeginRenderPass(cmdList.VkHandle, &rpBeginInfo, (inlineCommands ? VK_SUBPASS_CONTENTS_INLINE : VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS));
	}

	inline void VulkanEndRenderPass(HCmdList cmdList)
	{
		VkContext.vkCmdEndRenderPass(cmdList.VkHandle);
	}

	inline void VulkanBindViewports(HCmdList cmdList, Viewport* viewports, uint32_t viewportCount, uint32_t startIndex)
	{
		ASSERT_HANDLE_SIZE(Viewport, VkViewport);
		VkViewport* vulkanViewports = (VkViewport*)viewports;

		VkContext.vkCmdSetViewport(cmdList.VkHandle, startIndex, viewportCount, vulkanViewports);
	}

	inline void VulkanBindScissors(HCmdList cmdList, Scissor* scissors, uint32_t scissorCount, uint32_t startIndex)
	{
		ASSERT_HANDLE_SIZE(Scissor, VkRect2D);
		VkRect2D* vulkanScissors = (VkRect2D*)scissors;

		VkContext.vkCmdSetScissor(cmdList.VkHandle, startIndex, scissorCount, vulkanScissors);
	}

	inline void VulkanBindPipeline(HCmdList cmdList, HPipeline pipeline, EPipelineBindPoint bindPoint)
	{
		VkContext.vkCmdBindPipeline(cmdList.VkHandle, toVkPipelineBindPoint(bindPoint), pipeline.VkHandle);
	}

	inline void VulkanBindVertexBuffer(HCmdList cmdList, HBuffer vertexBuffer, uint32_t binding, uint32_t bindingCount, uint64_t offset)
	{
		VkContext.vkCmdBindVertexBuffers(cmdList.VkHandle, binding, bindingCount, &vertexBuffer.VkHandle.Buffer, &offset);
	}

	inline void VulkanBindIndexBuffer(HCmdList cmdList, HBuffer indexBuffer, EIndexType type, uint64_t offset)
	{
		VkContext.vkCmdBindIndexBuffer(cmdList.VkHandle, indexBuffer.VkHandle.Buffer, offset, toVkIndexType(type));
	}

	inline void VulkanBindDescriptorSets(HCmdList cmdList, HPipelineLayout layout, HDescriptorSet* sets, uint32_t descriptorSetCount, uint32_t startIndex, EPipelineBindPoint bindPoint)
	{
		ASSERT_HANDLE_SIZE(HDescriptorSet, VkDescriptorSet);
		VkDescriptorSet* vulkanSets = (VkDescriptorSet*)sets;

		VkContext.vkCmdBindDescriptorSets(cmdList.VkHandle, toVkPipelineBindPoint(bindPoint), layout.VkHandle, startIndex, descriptorSetCount, vulkanSets, 0, 0);
	}

	inline void VulkanDraw(HCmdList cmdList, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
	{
		VkContext.vkCmdDraw(cmdList.VkHandle, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	inline void VulkanDrawIndexed(HCmdList cmdList, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, uint32_t vertexOffset, uint32_t firstInstance)
	{
		VkContext.vkCmdDrawIndexed(cmdList.VkHandle, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
	}
}