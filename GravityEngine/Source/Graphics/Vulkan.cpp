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
import Platform;

namespace GFX
{
#pragma region enum_conversion

	VkFormat toVkFormat(Format format)
	{
		switch (format)
		{
		case FORMAT_UNDEFINED: return VK_FORMAT_UNDEFINED;
		case FORMAT_R8_UNORM: return VK_FORMAT_R8_UNORM;
		case FORMAT_R8_SNORM: return VK_FORMAT_R8_SNORM;
		case FORMAT_R8_USCALED: return VK_FORMAT_R8_USCALED;
		case FORMAT_R8_SSCALED: return VK_FORMAT_R8_SSCALED;
		case FORMAT_R8_UINT: return VK_FORMAT_R8_UINT;
		case FORMAT_R8_SINT: return VK_FORMAT_R8_SINT;
		case FORMAT_R8_SRGB: return VK_FORMAT_R8_SRGB;
		case FORMAT_R8G8_UNORM: return VK_FORMAT_R8G8_UNORM;
		case FORMAT_R8G8_SNORM: return VK_FORMAT_R8G8_SNORM;
		case FORMAT_R8G8_USCALED: return VK_FORMAT_R8G8_USCALED;
		case FORMAT_R8G8_SSCALED: return VK_FORMAT_R8G8_SSCALED;
		case FORMAT_R8G8_UINT: return VK_FORMAT_R8G8_UINT;
		case FORMAT_R8G8_SINT: return VK_FORMAT_R8G8_SINT;
		case FORMAT_R8G8_SRGB: return VK_FORMAT_R8G8_SRGB;
		case FORMAT_R8G8B8_UNORM: return VK_FORMAT_R8G8B8_UNORM;
		case FORMAT_R8G8B8_SNORM: return VK_FORMAT_R8G8B8_SNORM;
		case FORMAT_R8G8B8_USCALED: return VK_FORMAT_R8G8B8_USCALED;
		case FORMAT_R8G8B8_SSCALED: return VK_FORMAT_R8G8B8_SSCALED;
		case FORMAT_R8G8B8_UINT: return VK_FORMAT_R8G8B8_UINT;
		case FORMAT_R8G8B8_SINT: return VK_FORMAT_R8G8B8_SINT;
		case FORMAT_R8G8B8_SRGB: return VK_FORMAT_R8G8B8_SRGB;
		case FORMAT_B8G8R8_UNORM: return VK_FORMAT_B8G8R8_UNORM;
		case FORMAT_B8G8R8_SNORM: return VK_FORMAT_B8G8R8_SNORM;
		case FORMAT_B8G8R8_USCALED: return VK_FORMAT_B8G8R8_USCALED;
		case FORMAT_B8G8R8_SSCALED: return VK_FORMAT_B8G8R8_SSCALED;
		case FORMAT_B8G8R8_UINT: return VK_FORMAT_B8G8R8_UINT;
		case FORMAT_B8G8R8_SINT: return VK_FORMAT_B8G8R8_SINT;
		case FORMAT_B8G8R8_SRGB: return VK_FORMAT_B8G8R8_SRGB;
		case FORMAT_R8G8B8A8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM;
		case FORMAT_R8G8B8A8_SNORM: return VK_FORMAT_R8G8B8A8_SNORM;
		case FORMAT_R8G8B8A8_USCALED: return VK_FORMAT_R8G8B8A8_USCALED;
		case FORMAT_R8G8B8A8_SSCALED: return VK_FORMAT_R8G8B8A8_SSCALED;
		case FORMAT_R8G8B8A8_UINT: return VK_FORMAT_R8G8B8A8_UINT;
		case FORMAT_R8G8B8A8_SINT: return VK_FORMAT_R8G8B8A8_SINT;
		case FORMAT_R8G8B8A8_SRGB: return VK_FORMAT_R8G8B8A8_SRGB;
		case FORMAT_B8G8R8A8_UNORM: return VK_FORMAT_B8G8R8A8_UNORM;
		case FORMAT_B8G8R8A8_SNORM: return VK_FORMAT_B8G8R8A8_SNORM;
		case FORMAT_B8G8R8A8_USCALED: return VK_FORMAT_B8G8R8A8_USCALED;
		case FORMAT_B8G8R8A8_SSCALED: return VK_FORMAT_B8G8R8A8_SSCALED;
		case FORMAT_B8G8R8A8_UINT: return VK_FORMAT_B8G8R8A8_UINT;
		case FORMAT_B8G8R8A8_SINT: return VK_FORMAT_B8G8R8A8_SINT;
		case FORMAT_B8G8R8A8_SRGB: return VK_FORMAT_B8G8R8A8_SRGB;
		case FORMAT_R16_UNORM: return VK_FORMAT_R16_UNORM;
		case FORMAT_R16_SNORM: return VK_FORMAT_R16_SNORM;
		case FORMAT_R16_USCALED: return VK_FORMAT_R16_USCALED;
		case FORMAT_R16_SSCALED: return VK_FORMAT_R16_SSCALED;
		case FORMAT_R16_UINT: return VK_FORMAT_R16_UINT;
		case FORMAT_R16_SINT: return VK_FORMAT_R16_SINT;
		case FORMAT_R16_SFLOAT: return VK_FORMAT_R16_SFLOAT;
		case FORMAT_R16G16_UNORM: return VK_FORMAT_R16G16_UNORM;
		case FORMAT_R16G16_SNORM: return VK_FORMAT_R16G16_SNORM;
		case FORMAT_R16G16_USCALED: return VK_FORMAT_R16G16_USCALED;
		case FORMAT_R16G16_SSCALED: return VK_FORMAT_R16G16_SSCALED;
		case FORMAT_R16G16_UINT: return VK_FORMAT_R16G16_UINT;
		case FORMAT_R16G16_SINT: return VK_FORMAT_R16G16_SINT;
		case FORMAT_R16G16_SFLOAT: return VK_FORMAT_R16G16_SFLOAT;
		case FORMAT_R16G16B16_UNORM: return VK_FORMAT_R16G16B16_UNORM;
		case FORMAT_R16G16B16_SNORM: return VK_FORMAT_R16G16B16_SNORM;
		case FORMAT_R16G16B16_USCALED: return VK_FORMAT_R16G16B16_USCALED;
		case FORMAT_R16G16B16_SSCALED: return VK_FORMAT_R16G16B16_SSCALED;
		case FORMAT_R16G16B16_UINT: return VK_FORMAT_R16G16B16_UINT;
		case FORMAT_R16G16B16_SINT: return VK_FORMAT_R16G16B16_SINT;
		case FORMAT_R16G16B16_SFLOAT: return VK_FORMAT_R16G16B16_SFLOAT;
		case FORMAT_R16G16B16A16_UNORM: return VK_FORMAT_R16G16B16A16_UNORM;
		case FORMAT_R16G16B16A16_SNORM: return VK_FORMAT_R16G16B16A16_SNORM;
		case FORMAT_R16G16B16A16_USCALED: return VK_FORMAT_R16G16B16A16_USCALED;
		case FORMAT_R16G16B16A16_SSCALED: return VK_FORMAT_R16G16B16A16_SSCALED;
		case FORMAT_R16G16B16A16_UINT: return VK_FORMAT_R16G16B16A16_UINT;
		case FORMAT_R16G16B16A16_SINT: return VK_FORMAT_R16G16B16A16_SINT;
		case FORMAT_R16G16B16A16_SFLOAT: return VK_FORMAT_R16G16B16A16_SFLOAT;
		case FORMAT_R32_UINT: return VK_FORMAT_R32_UINT;
		case FORMAT_R32_SINT: return VK_FORMAT_R32_SINT;
		case FORMAT_R32_SFLOAT: return VK_FORMAT_R32_SFLOAT;
		case FORMAT_R32G32_UINT: return VK_FORMAT_R32G32_UINT;
		case FORMAT_R32G32_SINT: return VK_FORMAT_R32G32_SINT;
		case FORMAT_R32G32_SFLOAT: return VK_FORMAT_R32G32_SFLOAT;
		case FORMAT_R32G32B32_UINT: return VK_FORMAT_R32G32B32_UINT;
		case FORMAT_R32G32B32_SINT: return VK_FORMAT_R32G32B32_SINT;
		case FORMAT_R32G32B32_SFLOAT: return VK_FORMAT_R32G32B32_SFLOAT;
		case FORMAT_R32G32B32A32_UINT: return VK_FORMAT_R32G32B32A32_UINT;
		case FORMAT_R32G32B32A32_SINT: return VK_FORMAT_R32G32B32A32_SINT;
		case FORMAT_R32G32B32A32_SFLOAT: return VK_FORMAT_R32G32B32A32_SFLOAT;
		case FORMAT_R64_UINT: return VK_FORMAT_R64_UINT;
		case FORMAT_R64_SINT: return VK_FORMAT_R64_SINT;
		case FORMAT_R64_SFLOAT: return VK_FORMAT_R64_SFLOAT;
		case FORMAT_R64G64_UINT: return VK_FORMAT_R64G64_UINT;
		case FORMAT_R64G64_SINT: return VK_FORMAT_R64G64_SINT;
		case FORMAT_R64G64_SFLOAT: return VK_FORMAT_R64G64_SFLOAT;
		case FORMAT_R64G64B64_UINT: return VK_FORMAT_R64G64B64_UINT;
		case FORMAT_R64G64B64_SINT: return VK_FORMAT_R64G64B64_SINT;
		case FORMAT_R64G64B64_SFLOAT: return VK_FORMAT_R64G64B64_SFLOAT;
		case FORMAT_R64G64B64A64_UINT: return VK_FORMAT_R64G64B64A64_UINT;
		case FORMAT_R64G64B64A64_SINT: return VK_FORMAT_R64G64B64A64_SINT;
		case FORMAT_R64G64B64A64_SFLOAT: return VK_FORMAT_R64G64B64A64_SFLOAT;
		case FORMAT_D16_UNORM: return VK_FORMAT_D16_UNORM;
		case FORMAT_D32_SFLOAT: return VK_FORMAT_D32_SFLOAT;
		case FORMAT_S8_UINT: return VK_FORMAT_S8_UINT;
		case FORMAT_D16_UNORM_S8_UINT: return VK_FORMAT_D16_UNORM_S8_UINT;
		case FORMAT_D24_UNORM_S8_UINT: return VK_FORMAT_D24_UNORM_S8_UINT;
		case FORMAT_D32_SFLOAT_S8_UINT: return VK_FORMAT_D32_SFLOAT_S8_UINT;
		default: THROW_ERROR(); return VK_FORMAT_MAX_ENUM;
		}
	}

	VmaMemoryUsage toVkMemoryUsage(MemoryUsage usage)
	{
		switch (usage)
		{
		case MEMORY_USAGE_GPU_ONLY: return VMA_MEMORY_USAGE_GPU_ONLY;
		case MEMORY_USAGE_CPU_ONLY: return VMA_MEMORY_USAGE_CPU_ONLY;
		case MEMORY_USAGE_CPU_TO_GPU: return VMA_MEMORY_USAGE_CPU_TO_GPU;
		case MEMORY_USAGE_GPU_TO_CPU: return VMA_MEMORY_USAGE_GPU_TO_CPU;
		case MEMORY_USAGE_CPU_COPY: return VMA_MEMORY_USAGE_CPU_COPY;
		case MEMORY_USAGE_AUTO: return VMA_MEMORY_USAGE_AUTO;
		case MEMORY_USAGE_AUTO_PREFER_DEVICE: return VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;
		case MEMORY_USAGE_AUTO_PREFER_HOST: return VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
		default: THROW_ERROR(); return VMA_MEMORY_USAGE_UNKNOWN;
		}
	}

	VkCommandBufferLevel toVkCmdListLevel(CmdListLevel level)
	{
		switch (level)
		{
		case CMD_LIST_LEVEL_PRIMARY: return VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		case CMD_LIST_LEVEL_SECONDARY: return VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		default: THROW_ERROR(); return VK_COMMAND_BUFFER_LEVEL_MAX_ENUM;
		}
	}

	VkDescriptorType toVkDescriptorType(DescriptorType type)
	{
		switch (type)
		{
		case DESCRIPTOR_TYPE_SAMPLER: return VK_DESCRIPTOR_TYPE_SAMPLER;
		case DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER: return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		case DESCRIPTOR_TYPE_SAMPLED_IMAGE: return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
		case DESCRIPTOR_TYPE_STORAGE_IMAGE: return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
		case DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER: return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
		case DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER: return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
		case DESCRIPTOR_TYPE_UNIFORM_BUFFER: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		case DESCRIPTOR_TYPE_STORAGE_BUFFER: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		case DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
		case DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC: return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
		case DESCRIPTOR_TYPE_INPUT_ATTACHMENT: return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
		default: THROW_ERROR(); return VK_DESCRIPTOR_TYPE_MAX_ENUM;
		}
	}

	VkImageLayout toVkImageLayout(ImageLayout layout)
	{
		switch (layout)
		{
		case IMAGE_LAYOUT_UNDEFINED: return VK_IMAGE_LAYOUT_UNDEFINED;
		case IMAGE_LAYOUT_GENERAL: return VK_IMAGE_LAYOUT_GENERAL;
		case IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL: return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		case IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		case IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
		case IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL: return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		case IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL: return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		case IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL: return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		case IMAGE_LAYOUT_PREINITIALIZED: return VK_IMAGE_LAYOUT_PREINITIALIZED;
		case IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL: return VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL;
		case IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL: return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL;
		case IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL: return VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
		case IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL: return VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
		case IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL: return VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL;
		case IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL: return VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL;
		case IMAGE_LAYOUT_PRESENT_SRC: return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		default: THROW_ERROR(); return VK_IMAGE_LAYOUT_MAX_ENUM;
		}
	}

	VkImageType toVkImageType(ImageType type)
	{
		switch (type)
		{
		case IMAGE_TYPE_1D: return VK_IMAGE_TYPE_1D;
		case IMAGE_TYPE_2D: return VK_IMAGE_TYPE_2D;
		case IMAGE_TYPE_3D: return VK_IMAGE_TYPE_3D;
		default: THROW_ERROR(); return VK_IMAGE_TYPE_MAX_ENUM;
		}
	}

	VkImageTiling toVkImageTiling(ImageTiling tiling)
	{
		switch (tiling)
		{
		case IMAGE_TILING_OPTIMAL: return VK_IMAGE_TILING_OPTIMAL;
		case IMAGE_TILING_LINEAR: return VK_IMAGE_TILING_LINEAR;
		default: THROW_ERROR(); return VK_IMAGE_TILING_MAX_ENUM;
		}
	}

	VkImageViewType toVkImageViewType(ImageViewType type)
	{
		switch (type)
		{
		case IMAGE_VIEW_TYPE_1D: return VK_IMAGE_VIEW_TYPE_1D;
		case IMAGE_VIEW_TYPE_2D: return VK_IMAGE_VIEW_TYPE_2D;
		case IMAGE_VIEW_TYPE_3D: return VK_IMAGE_VIEW_TYPE_3D;
		default: THROW_ERROR(); return VK_IMAGE_VIEW_TYPE_MAX_ENUM;
		}
	}

	VkAttachmentLoadOp toVkLoadOp(LoadOp op)
	{
		switch (op)
		{
		case LOAD_OP_LOAD: return VK_ATTACHMENT_LOAD_OP_LOAD;
		case LOAD_OP_CLEAR: return VK_ATTACHMENT_LOAD_OP_CLEAR;
		case LOAD_OP_DONT_CARE: return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		default: THROW_ERROR(); return VK_ATTACHMENT_LOAD_OP_MAX_ENUM;
		}
	}

	VkAttachmentStoreOp toVkStoreOp(StoreOp op)
	{
		switch (op)
		{
		case STORE_OP_STORE: return VK_ATTACHMENT_STORE_OP_STORE;
		case STORE_OP_DONT_CARE: return VK_ATTACHMENT_STORE_OP_DONT_CARE;
		default: THROW_ERROR(); return VK_ATTACHMENT_STORE_OP_MAX_ENUM;
		}
	}

	VkPipelineBindPoint toVkPipelineBindPoint(PipelineBindPoint bindPoint)
	{
		switch (bindPoint)
		{
		case PIPELINE_BIND_POINT_GRAPHICS: return VK_PIPELINE_BIND_POINT_GRAPHICS;
		case PIPELINE_BIND_POINT_COMPUTE: return VK_PIPELINE_BIND_POINT_COMPUTE;
		case PIPELINE_BIND_POINT_RAY_TRACING: return VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
		default: THROW_ERROR(); return VK_PIPELINE_BIND_POINT_MAX_ENUM;
		}
	}

	shaderc_shader_kind toShadercShaderKind(ShaderStageFlags flags)
	{
		switch (flags)
		{
		case SHADER_STAGE_VERTEX_BIT: return shaderc_vertex_shader;
		case SHADER_STAGE_TESSELLATION_CONTROL_BIT: return shaderc_tess_control_shader;
		case SHADER_STAGE_TESSELLATION_EVALUATION_BIT: return shaderc_tess_evaluation_shader;
		case SHADER_STAGE_GEOMETRY_BIT: return shaderc_geometry_shader;
		case SHADER_STAGE_FRAGMENT_BIT: return shaderc_fragment_shader;
		case SHADER_STAGE_COMPUTE_BIT: return shaderc_task_shader;
		default: THROW_ERROR(); return (shaderc_shader_kind)UINT32_MAX;
		}
	}

	VkFilter toVkFilter(Filter filter)
	{
		switch (filter)
		{
		case FILTER_NEAREST: return VK_FILTER_NEAREST;
		case FILTER_LINEAR: return VK_FILTER_LINEAR;
		case FILTER_CUBIC_IMG: return VK_FILTER_CUBIC_IMG;
		default: THROW_ERROR(); return VK_FILTER_MAX_ENUM;
		}
	}

	VkSamplerAddressMode toVkAddressMode(AddressMode mode)
	{
		switch (mode)
		{
		case ADDRESS_MODE_REPEAT: return VK_SAMPLER_ADDRESS_MODE_REPEAT;
		case ADDRESS_MODE_MIRRORED_REPEAT: return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
		case ADDRESS_MODE_CLAMP_TO_EDGE: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		case ADDRESS_MODE_CLAMP_TO_BORDER: return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
		case ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE: return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
		default: THROW_ERROR(); return VK_SAMPLER_ADDRESS_MODE_MAX_ENUM;
		}
	}

	VkCompareOp toVkCompareOp(CompareOp op)
	{
		switch (op)
		{
		case COMPARE_OP_NEVER: return VK_COMPARE_OP_NEVER;
		case COMPARE_OP_LESS: return VK_COMPARE_OP_LESS;
		case COMPARE_OP_EQUAL: return VK_COMPARE_OP_EQUAL;
		case COMPARE_OP_LESS_OR_EQUAL: return VK_COMPARE_OP_LESS_OR_EQUAL;
		case COMPARE_OP_GREATER: return VK_COMPARE_OP_GREATER;
		case COMPARE_OP_NOT_EQUAL: return VK_COMPARE_OP_NOT_EQUAL;
		case COMPARE_OP_GREATER_OR_EQUAL: return VK_COMPARE_OP_GREATER_OR_EQUAL;
		case COMPARE_OP_ALWAYS: return VK_COMPARE_OP_ALWAYS;
		default: THROW_ERROR(); return VK_COMPARE_OP_MAX_ENUM;
		}
	}

	VkSamplerMipmapMode toVkMipmapMode(MipmapMode mode)
	{
		switch (mode)
		{
		case MIPMAP_MODE_NEAREST: return VK_SAMPLER_MIPMAP_MODE_NEAREST;
		case MIPMAP_MODE_LINEAR: return VK_SAMPLER_MIPMAP_MODE_LINEAR;
		default: THROW_ERROR(); return VK_SAMPLER_MIPMAP_MODE_MAX_ENUM;
		}
	}

	VkIndexType toVkIndexType(IndexType type)
	{
		switch (type)
		{
		case INDEX_TYPE_UINT16: return VK_INDEX_TYPE_UINT16;
		case INDEX_TYPE_UINT32: return VK_INDEX_TYPE_UINT32;
		default: THROW_ERROR(); return VK_INDEX_TYPE_MAX_ENUM;
		}
	}

	VkVertexInputRate toVkInputRate(InputRate rate)
	{
		switch (rate)
		{
		case INPUT_RATE_VERTEX: return VK_VERTEX_INPUT_RATE_VERTEX;
		case INPUT_RATE_INSTANCE: return VK_VERTEX_INPUT_RATE_INSTANCE;
		default: THROW_ERROR(); return VK_VERTEX_INPUT_RATE_MAX_ENUM;
		}
	}

	VkPrimitiveTopology toVkPrimitiveTopology(PrimitiveTopology topology)
	{
		switch (topology)
		{
		case PRIMITIVE_TOPOLOGY_POINT_LIST: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		case PRIMITIVE_TOPOLOGY_LINE_LIST: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		case PRIMITIVE_TOPOLOGY_LINE_STRIP: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
		case PRIMITIVE_TOPOLOGY_TRIANGLE_LIST: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		case PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		case PRIMITIVE_TOPOLOGY_TRIANGLE_FAN: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
		case PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
		case PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
		case PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
		case PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
		case PRIMITIVE_TOPOLOGY_PATCH_LIST: return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
		default: THROW_ERROR(); return VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
		}
	}

	VkPolygonMode toVkPolygonMode(PolygonMode mode)
	{
		switch (mode)
		{
		case POLYGON_MODE_FILL: return VK_POLYGON_MODE_FILL;
		case POLYGON_MODE_LINE: return VK_POLYGON_MODE_LINE;
		case POLYGON_MODE_POINT: return VK_POLYGON_MODE_POINT;
		default: THROW_ERROR(); return VK_POLYGON_MODE_MAX_ENUM;
		}
	}

	VkFrontFace toVkFrontFace(FrontFace front)
	{
		switch (front)
		{
		case FRONT_FACE_COUNTER_CLOCKWISE: return VK_FRONT_FACE_COUNTER_CLOCKWISE;
		case FRONT_FACE_CLOCKWISE: return VK_FRONT_FACE_CLOCKWISE;
		default: THROW_ERROR(); return VK_FRONT_FACE_MAX_ENUM;
		}
	}

	VkStencilOp toVkStencilOpState(StencilOp op)
	{
		switch (op)
		{
		case STENCIL_OP_KEEP: return VK_STENCIL_OP_KEEP;
		case STENCIL_OP_ZERO: return VK_STENCIL_OP_ZERO;
		case STENCIL_OP_REPLACE: return VK_STENCIL_OP_REPLACE;
		case STENCIL_OP_INCREMENT_AND_CLAMP: return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
		case STENCIL_OP_DECREMENT_AND_CLAMP: return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
		case STENCIL_OP_INVERT: return VK_STENCIL_OP_INVERT;
		case STENCIL_OP_INCREMENT_AND_WRAP: return VK_STENCIL_OP_INCREMENT_AND_WRAP;
		case STENCIL_OP_DECREMENT_AND_WRAP: return VK_STENCIL_OP_DECREMENT_AND_WRAP;
		default: THROW_ERROR(); return VK_STENCIL_OP_MAX_ENUM;
		}
	}

	VkBlendOp toVkBlendOp(BlendOp op)
	{
		switch (op)
		{
		case BLEND_OP_ADD: return VK_BLEND_OP_ADD;
		case BLEND_OP_SUBTRACT: return VK_BLEND_OP_SUBTRACT;
		case BLEND_OP_REVERSE_SUBTRACT: return VK_BLEND_OP_REVERSE_SUBTRACT;
		case BLEND_OP_MIN: return VK_BLEND_OP_MIN;
		case BLEND_OP_MAX: return VK_BLEND_OP_MAX;
		default: THROW_ERROR(); return VK_BLEND_OP_MAX_ENUM;
		}
	}

	VkBlendFactor toVkBlendFactor(BlendFactor factor)
	{
		switch (factor)
		{
		case BLEND_FACTOR_ZERO: return VK_BLEND_FACTOR_ZERO;
		case BLEND_FACTOR_ONE: return VK_BLEND_FACTOR_ONE;
		case BLEND_FACTOR_SRC_COLOR: return VK_BLEND_FACTOR_SRC_COLOR;
		case BLEND_FACTOR_ONE_MINUS_SRC_COLOR: return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
		case BLEND_FACTOR_DST_COLOR: return VK_BLEND_FACTOR_DST_COLOR;
		case BLEND_FACTOR_ONE_MINUS_DST_COLOR: return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
		case BLEND_FACTOR_SRC_ALPHA: return VK_BLEND_FACTOR_SRC_ALPHA;
		case BLEND_FACTOR_ONE_MINUS_SRC_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		case BLEND_FACTOR_DST_ALPHA: return VK_BLEND_FACTOR_DST_ALPHA;
		case BLEND_FACTOR_ONE_MINUS_DST_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
		case BLEND_FACTOR_CONSTANT_COLOR: return VK_BLEND_FACTOR_CONSTANT_COLOR;
		case BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
		case BLEND_FACTOR_CONSTANT_ALPHA: return VK_BLEND_FACTOR_CONSTANT_ALPHA;
		case BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA;
		case BLEND_FACTOR_SRC_ALPHA_SATURATE: return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
		case BLEND_FACTOR_SRC1_COLOR: return VK_BLEND_FACTOR_SRC1_COLOR;
		case BLEND_FACTOR_ONE_MINUS_SRC1_COLOR: return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
		case BLEND_FACTOR_SRC1_ALPHA: return VK_BLEND_FACTOR_SRC1_ALPHA;
		case BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
		default: THROW_ERROR(); return VK_BLEND_FACTOR_MAX_ENUM;
		}
	}

	VkLogicOp toVkLogicOp(LogicOp op)
	{
		switch (op)
		{
		case LOGIC_OP_CLEAR: return VK_LOGIC_OP_CLEAR;
		case LOGIC_OP_AND: return VK_LOGIC_OP_AND;
		case LOGIC_OP_AND_REVERSE: return VK_LOGIC_OP_AND_REVERSE;
		case LOGIC_OP_COPY: return VK_LOGIC_OP_COPY;
		case LOGIC_OP_AND_INVERTED: return VK_LOGIC_OP_AND_INVERTED;
		case LOGIC_OP_NO_OP: return VK_LOGIC_OP_NO_OP;
		case LOGIC_OP_XOR: return VK_LOGIC_OP_XOR;
		case LOGIC_OP_OR: return VK_LOGIC_OP_OR;
		case LOGIC_OP_NOR: return VK_LOGIC_OP_NOR;
		case LOGIC_OP_EQUIVALENT: return VK_LOGIC_OP_EQUIVALENT;
		case LOGIC_OP_INVERT: return VK_LOGIC_OP_INVERT;
		case LOGIC_OP_OR_REVERSE: return VK_LOGIC_OP_OR_REVERSE;
		case LOGIC_OP_COPY_INVERTED: return VK_LOGIC_OP_COPY_INVERTED;
		case LOGIC_OP_OR_INVERTED: return VK_LOGIC_OP_OR_INVERTED;
		case LOGIC_OP_NAND: return VK_LOGIC_OP_NAND;
		case LOGIC_OP_SET: return VK_LOGIC_OP_SET;
		default: THROW_ERROR(); return VK_LOGIC_OP_MAX_ENUM;
		}
	}

	VkSemaphoreType toVkSemaphoreType(SemaphoreType type)
	{
		switch (type)
		{
		case SEMAPHORE_TYPE_BINARY: return VK_SEMAPHORE_TYPE_BINARY;
		case SEMAPHORE_TYPE_TIMELINE: return VK_SEMAPHORE_TYPE_TIMELINE;
		default: THROW_ERROR(); return VK_SEMAPHORE_TYPE_MAX_ENUM;
		}
	}

	VkAccessFlags toVkAccessMask(AccessFlags flags)
	{
		return (VkAccessFlags)flags;
	}

	VkCommandBufferUsageFlags toVkCmdListUsageFlags(CmdListUsageFlags flags)
	{
		return (VkCommandBufferUsageFlags)flags;
	}

	VkPipelineStageFlags toVkPipelineStages(PipelineStageFlags flags)
	{
		return (VkPipelineStageFlags)flags;
	}

	VkImageUsageFlags toVkImageUsageFlags(ImageUsageFlags flags)
	{
		return (VkImageUsageFlags)flags;
	}

	VkImageAspectFlags toVkImageAspectFlags(ImageAspectFlags flags)
	{
		return (VkImageAspectFlags)flags;
	}

	VkDependencyFlags toVkDependencies(DependencyFlags flags)
	{
		return (VkDependencyFlags)flags;
	}

	VkShaderStageFlags toVkShaderStageFlags(ShaderStageFlags flags)
	{
		return (VkShaderStageFlags)flags;
	}

	VkCullModeFlags toVkCullModeFlags(CullModeFlags flags)
	{
		return (VkCullModeFlags)flags;
	}

	VkColorComponentFlags toVkColorFlags(ColorFlags flags)
	{
		return (VkColorComponentFlags)flags;
	}

	VkSampleCountFlags toVkSampleCountFlags(SampleCountFlags flags)
	{
		return (VkSampleCountFlags)flags;
	}

	VkBufferUsageFlags toVkBufferUsageFlags(BufferUsageFlags flags)
	{
		return (BufferUsageFlags)flags;
	}

#pragma endregion

#pragma region union_conversion
	
	inline MemoryCopyData VulkanInitMemoryCopyData(void* copyData, uint32_t dstOffset, uint32_t size)
	{
		MemoryCopyData data;
		data.VkObject.Data = copyData;
		data.VkObject.DstOffset = dstOffset;
		data.VkObject.Size = size;
		return data;
	}

	inline Offset3D VulkanInitOffset3D(int32_t x, int32_t y, int32_t z)
	{
		Offset3D data;
		data.VkObject.x = x;
		data.VkObject.y = y;
		data.VkObject.z = z;
		return data;
	}

	inline Extent3D VulkanInitExtent3D(uint32_t width, uint32_t height, uint32_t depth)
	{
		Extent3D data;
		data.VkObject.width = width;
		data.VkObject.height= height;
		data.VkObject.depth = depth;
		return data;
	}

	inline BufferCopyData VulkanInitBufferCopyData(uint32_t srcOffset, uint32_t dstOffset, uint32_t size)
	{
		BufferCopyData data;
		data.VkObject.srcOffset = srcOffset;
		data.VkObject.dstOffset = dstOffset;
		data.VkObject.size = size;
		return data;
	}

	inline ClearValue VulkanInitClearValue(const float float32[4], const int32_t int32[4], const uint32_t uint32[4], float depth, uint32_t stencil)
	{
		ClearValue data;
		if (float32 != nullptr) {
			data.VkObject.color.float32[0] = float32[0];
			data.VkObject.color.float32[1] = float32[1];
			data.VkObject.color.float32[2] = float32[2];
			data.VkObject.color.float32[3] = float32[3];
			return data;
		}
		else if (int32 != nullptr) {
			data.VkObject.color.int32[0] = int32[0];
			data.VkObject.color.int32[1] = int32[1];
			data.VkObject.color.int32[2] = int32[2];
			data.VkObject.color.int32[3] = int32[3];
			return data;
		}
		else if (uint32 != nullptr) {
			data.VkObject.color.uint32[0] = uint32[0];
			data.VkObject.color.uint32[1] = uint32[1];
			data.VkObject.color.uint32[2] = uint32[2];
			data.VkObject.color.uint32[3] = uint32[3];
			return data;
		}
		else {
			data.VkObject.depthStencil.depth = depth;
			data.VkObject.depthStencil.stencil = stencil;
			return data;
		}
	}

	inline Scissor VulkanInitScissor(uint32_t width, uint32_t height, int32_t x, int32_t y)
	{
		Scissor data;
		data.VkObject.extent.width = width;
		data.VkObject.extent.height = height;
		data.VkObject.offset.x = x;
		data.VkObject.offset.y = y;
		return data;
	}

	inline Viewport VulkanInitViewport(float x, float y, float width, float height, float minDepth, float maxDepth)
	{
		Viewport data;
		data.VkObject.x = x;
		data.VkObject.y = y;
		data.VkObject.width = width;
		data.VkObject.height = height;
		data.VkObject.minDepth = minDepth;
		data.VkObject.maxDepth = maxDepth;
		return data;
	}	

	inline BufferImageCopyData VulkanInitBufferImageCopyData(uint64_t srcOffset, uint32_t bufferRowLength, uint32_t bufferImageHeight, Offset3D imageOffset, Extent3D imageExtent, const ImageSubresourceLayers& subresource)
	{
		BufferImageCopyData data;
		data.VkObject.bufferOffset = srcOffset;
		data.VkObject.bufferRowLength = bufferRowLength;
		data.VkObject.bufferImageHeight = bufferImageHeight;
		data.VkObject.imageExtent = imageExtent.VkObject;
		data.VkObject.imageOffset = imageOffset.VkObject;
		data.VkObject.imageSubresource = subresource.VkObject;
		return data;
	}

	inline ImageSubresourceLayers VulkanInitImageSubresourceLayers(ImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t baseLayer, uint32_t layerCount)
	{
		ImageSubresourceLayers data;
		data.VkObject.aspectMask = toVkImageAspectFlags(aspectMask);
		data.VkObject.mipLevel = mipLevel;
		data.VkObject.baseArrayLayer = baseLayer;
		data.VkObject.layerCount = layerCount;
		return data;
	}

	inline ImageSubresourceRange VulkanInitImageSubresourceRange(ImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t levelCount, uint32_t baseLayer, uint32_t layerCount)
	{
		ImageSubresourceRange data;
		data.VkObject.aspectMask = toVkImageAspectFlags(aspectMask);
		data.VkObject.baseMipLevel = mipLevel;
		data.VkObject.levelCount = levelCount;
		data.VkObject.baseArrayLayer = baseLayer;
		data.VkObject.layerCount = layerCount;
		return data;
	}

	inline DescriptorPoolSize VulkanInitDescriptorPoolSize(DescriptorType type, uint32_t count)
	{
		DescriptorPoolSize data;
		data.VkObject.type = toVkDescriptorType(type);
		data.VkObject.descriptorCount = count;
		return data;
	}

	inline DescriptorLayoutBinding VulkanInitDescriptorLayoutBinding(uint32_t binding, DescriptorType type, uint32_t count, ShaderStageFlags shaderStageFlags)
	{
		DescriptorLayoutBinding data;
		data.VkObject.binding = binding;
		data.VkObject.descriptorType = toVkDescriptorType(type);
		data.VkObject.descriptorCount = count;
		data.VkObject.stageFlags = toVkShaderStageFlags(shaderStageFlags);
		data.VkObject.pImmutableSamplers = nullptr;
		return data;
	}

	inline DescriptorBufferInfo VulkanInitDescriptorBufferInfo(Buffer buffer, uint64_t offset, uint64_t range)
	{
		DescriptorBufferInfo data;
		data.VkObject.buffer = buffer.VkHandle.Buffer;
		data.VkObject.offset = offset;
		data.VkObject.range = range;
		return data;
	}

	inline DescriptorImageInfo VulkanInitDescriptorImageInfo(ImageView imageView, Sampler sampler, ImageLayout imageLayout)
	{
		DescriptorImageInfo data;
		data.VkObject.imageView = imageView.VkHandle;
		data.VkObject.sampler = sampler.VkHandle;
		data.VkObject.imageLayout = toVkImageLayout(imageLayout);
		return data;
	}

	inline DescriptorWriteData VulkanInitDescriptorWriteData(DescriptorSet dstSet, uint32_t binding, uint32_t index, DescriptorType type, const DescriptorImageInfo* imageInfo, const DescriptorBufferInfo* bufferInfo, uint32_t count)
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

	inline AttachmentDescription VulkanInitAttachmentDescription(Format format, SampleCountFlags sampleCount, LoadOp lop, StoreOp sop, LoadOp stencilLop, StoreOp stencilSop, ImageLayout initialLayout, ImageLayout finalLayout)
	{
		AttachmentDescription data;
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

	inline AttachmentReference VulkanInitAttachmentReference(uint32_t attachment, ImageLayout layout)
	{
		AttachmentReference data; 
		data.VkObject.attachment = attachment;
		data.VkObject.layout = toVkImageLayout(layout);
		return data;
	}

	inline SubpassDescription VulkanInitSubpassDescription(PipelineBindPoint bindPoint, const AttachmentReference* inputs, uint32_t inputCount, const AttachmentReference* colors, const AttachmentReference* resolves, uint32_t colorCount, const AttachmentReference* depthStencil, const uint32_t* reserves, uint32_t reserveCount)
	{
		ASSERT_HANDLE_SIZE(AttachmentReference, VkAttachmentReference);
		VkAttachmentReference* vulkanInputs = (VkAttachmentReference*)inputs;
		VkAttachmentReference* vulkanColors = (VkAttachmentReference*)colors;
		VkAttachmentReference* vulkanResolves = (VkAttachmentReference*)resolves;
		VkAttachmentReference* vulkanDepthStencil = (VkAttachmentReference*)depthStencil;

		SubpassDescription data;
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

	inline SubpassDependency VulkanInitSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass, PipelineStageFlags srcStages, PipelineStageFlags dstStages, AccessFlags srcAccess, AccessFlags dstAccess, DependencyFlags dependencyFlags)
	{
		SubpassDependency data;
		data.VkObject.srcSubpass = srcSubpass;
		data.VkObject.dstSubpass = dstSubpass;
		data.VkObject.srcStageMask = toVkPipelineStages(srcStages);
		data.VkObject.dstStageMask = toVkPipelineStages(dstStages);
		data.VkObject.srcAccessMask = toVkAccessMask(srcAccess);
		data.VkObject.dstAccessMask = toVkAccessMask(dstAccess);
		data.VkObject.dependencyFlags = toVkDependencies(dependencyFlags);
		return data;
	}

	inline BufferCreateInfo VulkanInitBufferCreateInfo(uint64_t size, BufferUsageFlags bufferUsage, MemoryUsage memoryUsage)
	{
		BufferCreateInfo data;
		data.VkObject.BufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		data.VkObject.BufferInfo.pNext = nullptr;
		data.VkObject.BufferInfo.flags = 0;
		data.VkObject.BufferInfo.size = size;
		data.VkObject.BufferInfo.usage = toVkBufferUsageFlags(bufferUsage);
		data.VkObject.BufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		data.VkObject.BufferInfo.pQueueFamilyIndices = nullptr;
		data.VkObject.BufferInfo.queueFamilyIndexCount = 0;
		data.VkObject.AllocInfo.flags = 0;
		data.VkObject.AllocInfo.memoryTypeBits = 0;
		data.VkObject.AllocInfo.pool = nullptr;
		data.VkObject.AllocInfo.requiredFlags = 0;
		data.VkObject.AllocInfo.preferredFlags = 0;
		data.VkObject.AllocInfo.priority = 0;
		data.VkObject.AllocInfo.usage = toVkMemoryUsage(memoryUsage);

		return data;
	}

	inline ImageCreateInfo VulkanInitImageCreateInfo(ImageType type, Format format, Extent3D extent, uint32_t mipLevels, uint32_t arrayLayers, SampleCountFlags sampleCount, ImageTiling tiling, ImageLayout initialLayout, ImageUsageFlags imageUsage)
	{
		ImageCreateInfo data;
		data.VkObject.ImageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		data.VkObject.ImageInfo.pNext = nullptr;
		data.VkObject.ImageInfo.flags = 0;
		data.VkObject.ImageInfo.imageType = toVkImageType(type);
		data.VkObject.ImageInfo.format = toVkFormat(format);
		data.VkObject.ImageInfo.extent = extent.VkObject;
		data.VkObject.ImageInfo.mipLevels = mipLevels;
		data.VkObject.ImageInfo.arrayLayers = arrayLayers;
		data.VkObject.ImageInfo.samples = (VkSampleCountFlagBits)toVkSampleCountFlags(sampleCount);
		data.VkObject.ImageInfo.tiling = toVkImageTiling(tiling);
		data.VkObject.ImageInfo.initialLayout = toVkImageLayout(initialLayout);
		data.VkObject.ImageInfo.usage = toVkImageUsageFlags(imageUsage);
		data.VkObject.ImageInfo.pQueueFamilyIndices = nullptr;
		data.VkObject.ImageInfo.queueFamilyIndexCount = 0;
		data.VkObject.ImageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		data.VkObject.AllocInfo.flags = 0;
		data.VkObject.AllocInfo.memoryTypeBits = 0;
		data.VkObject.AllocInfo.pool = nullptr;
		data.VkObject.AllocInfo.requiredFlags = 0;
		data.VkObject.AllocInfo.preferredFlags = 0;
		data.VkObject.AllocInfo.priority = 0;
		data.VkObject.AllocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;
		return data;
	}

	inline ImageViewCreateInfo VulkanInitImageViewCreateInfo(Image image, ImageViewType type, Format format, const ImageSubresourceRange& subresource)
	{
		ImageViewCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.image = image.VkHandle.Image;
		data.VkObject.viewType = toVkImageViewType(type);
		data.VkObject.format = toVkFormat(format);
		data.VkObject.components.r = VK_COMPONENT_SWIZZLE_R;
		data.VkObject.components.g = VK_COMPONENT_SWIZZLE_G;
		data.VkObject.components.b = VK_COMPONENT_SWIZZLE_B;
		data.VkObject.components.a = VK_COMPONENT_SWIZZLE_A;
		data.VkObject.subresourceRange = subresource.VkObject;
		return data;
	}

	inline CmdPoolCreateInfo VulkanInitCmdPoolCreateInfo(uint32_t queueFamilyIndex)
	{
		CmdPoolCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.queueFamilyIndex = queueFamilyIndex;
		return data;
	}

	inline CmdListsCreateInfo VulkanInitCmdListsCreateInfo(CmdPool pool, CmdListLevel level, uint32_t count)
	{
		CmdListsCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.commandPool = pool.VkHandle;
		data.VkObject.level = toVkCmdListLevel(level);
		data.VkObject.commandBufferCount = count;
		return data;
	}

	inline ShaderStageInfo VulkanInitShaderStageInfo(Shader shader, ShaderStageFlags stage, const char* name)
	{
		ShaderStageInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.module = shader.VkHandle;
		data.VkObject.stage = (VkShaderStageFlagBits)toVkShaderStageFlags(stage);
		data.VkObject.pName = name;
		data.VkObject.pSpecializationInfo = nullptr;
		return data;
	}

	inline VertexBinding VulkanInitVertexBinding(uint32_t binding, uint32_t stride, InputRate inputRate)
	{
		VertexBinding data;
		data.VkObject.binding = binding;
		data.VkObject.stride = stride;
		data.VkObject.inputRate = toVkInputRate(inputRate);
		return data;
	}

	inline VertexAttribute VulkanInitVertexAttribute(uint32_t binding, uint32_t location, uint32_t offset, Format format)
	{
		VertexAttribute data;
		data.VkObject.binding = binding;
		data.VkObject.location = location;
		data.VkObject.offset = offset;
		data.VkObject.format = toVkFormat(format);
		return data;
	}

	inline VertexInputInfo VulkanInitVertexInputInfo(const VertexBinding* bindings, uint32_t bindingCount, const VertexAttribute* attributes, uint32_t attributeCount)
	{
		ASSERT_HANDLE_SIZE(VertexBinding, VkVertexInputBindingDescription);
		ASSERT_HANDLE_SIZE(VertexAttribute, VkVertexInputAttributeDescription);
		VkVertexInputBindingDescription* vulkanBindings = (VkVertexInputBindingDescription*)bindings;
		VkVertexInputAttributeDescription* vulkanAttributes = (VkVertexInputAttributeDescription*)attributes;

		VertexInputInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.pVertexBindingDescriptions = vulkanBindings;
		data.VkObject.vertexBindingDescriptionCount = bindingCount;
		data.VkObject.pVertexAttributeDescriptions = vulkanAttributes;
		data.VkObject.vertexAttributeDescriptionCount = attributeCount;
		return data;
	}

	inline InputAssemblyInfo VulkanInitInputAssemblyInfo(PrimitiveTopology topology, bool primitiveRestart)
	{
		InputAssemblyInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.primitiveRestartEnable = primitiveRestart;
		data.VkObject.topology = toVkPrimitiveTopology(topology);
		return data;
	}

	inline TessellationInfo VulkanInitTessellationInfo(uint32_t patchControlPoints)
	{
		TessellationInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.patchControlPoints = patchControlPoints;
		return data;
	}

	inline ViewportInfo VulkanInitViewportInfo(const Viewport* viewports, uint32_t viewportCount, const Scissor* scissors, uint32_t scissorCount)
	{
		ASSERT_HANDLE_SIZE(Viewport, VkViewport);
		ASSERT_HANDLE_SIZE(Scissor, VkRect2D);
		VkViewport* vulkanViewports = (VkViewport*)viewports;
		VkRect2D* vulkanScissors = (VkRect2D*)scissors;

		ViewportInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.pViewports = vulkanViewports;
		data.VkObject.viewportCount = viewportCount;
		data.VkObject.pScissors = vulkanScissors;
		data.VkObject.scissorCount = scissorCount;
		return data;
	}

	inline RasterizationInfo VulkanInitRasterizationInfo(PolygonMode polyMode, CullModeFlags cullMode, FrontFace frontFace, bool depthClamp, bool rasterizationDiscard, bool depthBias, float depthBiasConstant, float depthBiasClamp, float depthBiasSlope, float lineWidth)
	{
		RasterizationInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.polygonMode = toVkPolygonMode(polyMode);
		data.VkObject.cullMode = toVkCullModeFlags(cullMode);
		data.VkObject.frontFace = toVkFrontFace(frontFace);
		data.VkObject.depthClampEnable = depthClamp;
		data.VkObject.rasterizerDiscardEnable = rasterizationDiscard;
		data.VkObject.depthBiasClamp = depthBiasClamp;
		data.VkObject.depthBiasConstantFactor = depthBiasConstant;
		data.VkObject.depthBiasSlopeFactor = depthBiasSlope;
		data.VkObject.lineWidth = lineWidth;
		return data;
	}

	inline MultisamplingInfo VulkanInitMultisamplingInfo(SampleCountFlags sampleCount, bool alphaToCoverage, bool alphaToOne, bool sampleShading, float minSampleShading)
	{
		MultisamplingInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.rasterizationSamples = (VkSampleCountFlagBits)toVkSampleCountFlags(sampleCount);
		data.VkObject.alphaToCoverageEnable = alphaToCoverage;
		data.VkObject.alphaToOneEnable = alphaToOne;
		data.VkObject.sampleShadingEnable = sampleShading;
		data.VkObject.minSampleShading = minSampleShading;
		data.VkObject.pSampleMask = nullptr;
		return data;
	}

	inline StencilOpState VulkanInitStencilOpState(StencilOp fail, StencilOp pass, StencilOp depthFail, CompareOp compare, uint32_t compareMask, uint32_t writeMask, uint32_t reference)
	{
		StencilOpState data;
		data.VkObject.failOp = toVkStencilOpState(fail);
		data.VkObject.passOp = toVkStencilOpState(pass);
		data.VkObject.depthFailOp = toVkStencilOpState(depthFail);
		data.VkObject.compareOp = toVkCompareOp(compare);
		data.VkObject.compareMask = compareMask;
		data.VkObject.writeMask = writeMask;
		data.VkObject.reference = reference;
		return data;
	}

	inline DepthStencilInfo VulkanInitDepthStencilInfo(bool depthTest, bool depthWrite, bool depthBoundsTest, bool stencilTest, CompareOp op, StencilOpState front, StencilOpState back, float minBounds, float maxBounds)
	{
		DepthStencilInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.depthTestEnable = depthTest;
		data.VkObject.depthWriteEnable = depthWrite;
		data.VkObject.depthBoundsTestEnable = depthBoundsTest;
		data.VkObject.stencilTestEnable = stencilTest;
		data.VkObject.depthCompareOp = toVkCompareOp(op);
		data.VkObject.front = front.VkObject;
		data.VkObject.back = back.VkObject;
		return data;
	}

	inline ColorBlendAttachmentState VulkanInitColorBlendAttachmentState(bool blend, BlendOp blendOp, BlendOp alphaBlendOp, ColorFlags writeMask, BlendFactor srcBlend, BlendFactor dstBlend, BlendFactor srcAlphaBlend, BlendFactor dstAlphaBlend)
	{
		ColorBlendAttachmentState data;
		data.VkObject.blendEnable = blend;
		data.VkObject.colorBlendOp = toVkBlendOp(blendOp);
		data.VkObject.alphaBlendOp = toVkBlendOp(alphaBlendOp);
		data.VkObject.colorWriteMask = toVkColorFlags(writeMask);
		data.VkObject.srcColorBlendFactor = toVkBlendFactor(srcBlend);
		data.VkObject.dstColorBlendFactor = toVkBlendFactor(dstBlend);
		data.VkObject.srcAlphaBlendFactor = toVkBlendFactor(srcAlphaBlend);
		data.VkObject.dstAlphaBlendFactor = toVkBlendFactor(dstAlphaBlend);
		return data;
	}

	inline ColorBlendInfo VulkanInitColorBlendInfo(bool logicOp, LogicOp op, const ColorBlendAttachmentState* attachments, uint32_t attachmentCount, float blendConstants[4])
	{
		ASSERT_HANDLE_SIZE(ColorBlendAttachmentState, VkPipelineColorBlendAttachmentState);
		VkPipelineColorBlendAttachmentState* vulkanAttachments = (VkPipelineColorBlendAttachmentState*)attachments;

		ColorBlendInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.logicOpEnable = logicOp;
		data.VkObject.logicOp = toVkLogicOp(op);
		data.VkObject.pAttachments = vulkanAttachments;
		data.VkObject.attachmentCount = attachmentCount;
		data.VkObject.blendConstants[0] = blendConstants[0];
		data.VkObject.blendConstants[1] = blendConstants[1];
		data.VkObject.blendConstants[2] = blendConstants[2];
		data.VkObject.blendConstants[3] = blendConstants[3];
		return data;
	}

	inline DynamicInfo VulkanInitDynamicInfo(const DynamicState* states, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(DynamicState, VkDynamicState);
		VkDynamicState* vulkanStates = (VkDynamicState*)states;
		
		DynamicInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.pDynamicStates = vulkanStates;
		data.VkObject.dynamicStateCount = count;
		return data;
	}

	inline GraphicsPipelineCreateInfo VulkanInitGraphicsPipelineCreateInfo(
		PipelineLayout layout, RenderPass renderPass, uint32_t subpass,
		const ShaderStageInfo* stageInfos, uint32_t stageCount,
		const VertexInputInfo& vertexInfo,
		const InputAssemblyInfo& inputAssemblyInfo,
		const TessellationInfo& tessellationInfo,
		const ViewportInfo& viewportInfo,
		const RasterizationInfo& rasterizationInfo,
		const MultisamplingInfo& multisamplingInfo,
		const DepthStencilInfo& depthStencilInfo,
		const ColorBlendInfo& colorBlendInfo,
		const DynamicInfo& dynamicInfo)
	{
		ASSERT_HANDLE_SIZE(ShaderStageInfo, VkPipelineShaderStageCreateInfo);
		VkPipelineShaderStageCreateInfo* vulkanStageInfos = (VkPipelineShaderStageCreateInfo*)stageInfos;

		GraphicsPipelineCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.layout = layout.VkHandle;
		data.VkObject.renderPass = renderPass.VkHandle;
		data.VkObject.subpass = subpass;
		data.VkObject.pStages = vulkanStageInfos;
		data.VkObject.stageCount = stageCount;
		data.VkObject.pVertexInputState = &vertexInfo.VkObject;
		data.VkObject.pInputAssemblyState = &inputAssemblyInfo.VkObject;
		data.VkObject.pTessellationState = &tessellationInfo.VkObject;
		data.VkObject.pViewportState = &viewportInfo.VkObject;
		data.VkObject.pRasterizationState = &rasterizationInfo.VkObject;
		data.VkObject.pMultisampleState = &multisamplingInfo.VkObject;
		data.VkObject.pDepthStencilState = &depthStencilInfo.VkObject;
		data.VkObject.pColorBlendState = &colorBlendInfo.VkObject;
		data.VkObject.pDynamicState = &dynamicInfo.VkObject;
		data.VkObject.basePipelineHandle = nullptr;
		data.VkObject.basePipelineIndex = 0;
		return data;
	}

	inline PushConstant VulkanInitPushConstant(ShaderStageFlags stages, uint32_t offset, uint32_t size)
	{
		PushConstant data;
		data.VkObject.stageFlags = toVkShaderStageFlags(stages);
		data.VkObject.offset = offset;
		data.VkObject.size = size;
		return data;
	}

	inline PipelineLayoutCreateInfo VulkanInitPipelineLayoutCreateInfo(const DescriptorLayout* layouts, uint32_t layoutCount, const PushConstant* pushConstants, uint32_t pushConstantCount)
	{
		ASSERT_HANDLE_SIZE(DescriptorLayout, VkDescriptorSetLayout);
		ASSERT_HANDLE_SIZE(PushConstant, VkPushConstantRange);
		VkDescriptorSetLayout* vulkanLayouts = (VkDescriptorSetLayout*)layouts;
		VkPushConstantRange* vulkanPushConstants = (VkPushConstantRange*)pushConstants;

		PipelineLayoutCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.pSetLayouts = vulkanLayouts;
		data.VkObject.setLayoutCount = layoutCount;
		data.VkObject.pPushConstantRanges = vulkanPushConstants;
		data.VkObject.pushConstantRangeCount = pushConstantCount;
		return data;
	}

	inline RenderPassCreateInfo VulkanInitRenderPassCreateInfo(const AttachmentDescription* attachments, uint32_t attachmentCount, const SubpassDescription* subpasses, uint32_t subpassCount, const SubpassDependency* dependencies, uint32_t dependencyCount)
	{
		ASSERT_HANDLE_SIZE(AttachmentDescription, VkAttachmentDescription);
		ASSERT_HANDLE_SIZE(SubpassDescription, VkSubpassDescription);
		ASSERT_HANDLE_SIZE(SubpassDependency, VkSubpassDependency);
		VkAttachmentDescription* vulkanAttachments = (VkAttachmentDescription*)attachments;
		VkSubpassDescription* vulkanSubpasses = (VkSubpassDescription*)subpasses;
		VkSubpassDependency* vulkanDependencies = (VkSubpassDependency*)dependencies;

		RenderPassCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.attachmentCount = attachmentCount;
		data.VkObject.pAttachments = vulkanAttachments;
		data.VkObject.subpassCount = subpassCount;
		data.VkObject.pSubpasses = vulkanSubpasses;
		data.VkObject.dependencyCount = dependencyCount;
		data.VkObject.pDependencies = vulkanDependencies;
		return data;
	}

	inline FramebufferCreateInfo VulkanInitFramebufferCreateInfo(RenderPass renderPass, const ImageView* attachments, uint32_t attachmentCount, uint32_t width, uint32_t height, uint32_t layers)
	{
		ASSERT_HANDLE_SIZE(ImageView, VkImageView);
		VkImageView* vulkanAttachments = (VkImageView*)attachments;

		FramebufferCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.renderPass = renderPass.VkHandle;
		data.VkObject.attachmentCount = attachmentCount;
		data.VkObject.pAttachments = vulkanAttachments;
		data.VkObject.width = width;
		data.VkObject.height = height;
		data.VkObject.layers = layers;
		return data;
	}

	inline DescriptorSetsCreateInfo VulkanInitDescriptorSetsCreateInfo(DescriptorPool pool, const DescriptorLayout* layouts, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(DescriptorLayout, VkDescriptorSetLayout);
		VkDescriptorSetLayout* vulkanLayouts = (VkDescriptorSetLayout*)layouts;

		DescriptorSetsCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.descriptorPool = pool.VkHandle;
		data.VkObject.pSetLayouts = vulkanLayouts;
		data.VkObject.descriptorSetCount = count;
		return data;
	}

	inline DescriptorLayoutCreateInfo VulkanInitDescriptorLayoutCreateInfo(const DescriptorLayoutBinding* bindings, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(DescriptorLayoutBinding, VkDescriptorSetLayoutBinding);
		VkDescriptorSetLayoutBinding* vulkanBindings = (VkDescriptorSetLayoutBinding*)bindings;

		DescriptorLayoutCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.pBindings = vulkanBindings;
		data.VkObject.bindingCount = count;
		return data;
	}

	inline DescriptorPoolCreateInfo VulkanInitDescriptorPoolCreateInfo(const DescriptorPoolSize* poolSizes, uint32_t count, uint32_t maxSets)
	{
		ASSERT_HANDLE_SIZE(DescriptorPoolSize, VkDescriptorPoolSize);
		VkDescriptorPoolSize* vulkanPoolSizes = (VkDescriptorPoolSize*)poolSizes;

		DescriptorPoolCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.flags = 0;
		data.VkObject.poolSizeCount = count;
		data.VkObject.pPoolSizes = vulkanPoolSizes;
		data.VkObject.maxSets = maxSets;
		return data;
	}
	
	inline SubmitTimelineInfo VulkanInitSubmitTimelineInfo(const uint64_t* waitValues, uint32_t waitCount, const uint64_t* signalValues, uint32_t signalCount)
	{
		SubmitTimelineInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.pWaitSemaphoreValues = waitValues;
		data.VkObject.waitSemaphoreValueCount = waitCount;
		data.VkObject.pSignalSemaphoreValues = signalValues;
		data.VkObject.signalSemaphoreValueCount = signalCount;
		return data;
	}

	inline SubmitInfo VulkanInitSubmitInfo(const CmdList* cmdLists, const PipelineStageFlags* waitStages, uint32_t cmdListCount, const Semaphore* waitSemaphores, uint32_t waitCount, const Semaphore* signalSemaphores, uint32_t signalCount, const SubmitTimelineInfo* timelineInfo)
	{
		ASSERT_HANDLE_SIZE(CmdList, VkCommandBuffer);
		ASSERT_HANDLE_SIZE(Semaphore, VkSemaphore);
		ASSERT_HANDLE_SIZE(PipelineStageFlags, VkPipelineStageFlags);
		VkCommandBuffer* vulkanCmdLists = (VkCommandBuffer*)cmdLists;
		VkSemaphore* vulkanSignalSemaphores = (VkSemaphore*)signalSemaphores;
		VkSemaphore* vulkanWaitSemaphores = (VkSemaphore*)waitSemaphores;
		VkPipelineStageFlags* vulkanStageFlags = (VkPipelineStageFlags*)waitStages;

		SubmitInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		data.VkObject.pNext = &timelineInfo->VkObject;
		data.VkObject.pWaitDstStageMask = vulkanStageFlags;
		data.VkObject.waitSemaphoreCount = waitCount;
		data.VkObject.pWaitSemaphores = vulkanWaitSemaphores;
		data.VkObject.commandBufferCount = cmdListCount;
		data.VkObject.pCommandBuffers = vulkanCmdLists;
		data.VkObject.signalSemaphoreCount = signalCount;
		data.VkObject.pSignalSemaphores = vulkanSignalSemaphores;
		return data;
	}

	inline BeginRecordingInfo VulkanInitBeginRecordingInfo(RenderPass renderPass, uint32_t subpass, Framebuffer framebuffer, CmdListUsageFlags usage)
	{
		BeginRecordingInfo data;
		data.VkObject.InheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
		data.VkObject.InheritanceInfo.pNext = nullptr;
		data.VkObject.InheritanceInfo.renderPass = renderPass.VkHandle;
		data.VkObject.InheritanceInfo.subpass = subpass;
		data.VkObject.InheritanceInfo.framebuffer = framebuffer.VkHandle;
		data.VkObject.InheritanceInfo.occlusionQueryEnable = false;
		data.VkObject.InheritanceInfo.queryFlags = 0;
		data.VkObject.InheritanceInfo.pipelineStatistics = 0;
		data.VkObject.BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		data.VkObject.BeginInfo.pNext = nullptr;
		data.VkObject.BeginInfo.flags = toVkCmdListUsageFlags(usage);
		data.VkObject.BeginInfo.pInheritanceInfo = &data.VkObject.InheritanceInfo;
		return data;
	}

	inline SamplerCreateInfo VulkanInitSamplerCreateInfo(Filter magFilter, Filter minFilter, MipmapMode mipMode, AddressMode U, AddressMode V, AddressMode W, bool anisotropy, float maxAnisotropy, float mipBias, float minLod, float maxLod, bool compare, CompareOp op)
	{
		SamplerCreateInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		data.VkObject.pNext = VK_NULL_HANDLE;
		data.VkObject.flags = 0;
		data.VkObject.magFilter = toVkFilter(magFilter);
		data.VkObject.minFilter = toVkFilter(minFilter);
		data.VkObject.addressModeU = toVkAddressMode(U);
		data.VkObject.addressModeV = toVkAddressMode(V);
		data.VkObject.addressModeW = toVkAddressMode(W);
		data.VkObject.anisotropyEnable = anisotropy;
		data.VkObject.maxAnisotropy = maxAnisotropy;
		data.VkObject.compareEnable = compare;
		data.VkObject.compareOp = toVkCompareOp(op);
		data.VkObject.mipmapMode = toVkMipmapMode(mipMode);
		data.VkObject.mipLodBias = mipBias;
		data.VkObject.minLod = minLod;
		data.VkObject.maxLod = maxLod;
		data.VkObject.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		data.VkObject.unnormalizedCoordinates = VK_FALSE;
		return data;
	}

	inline RenderPassBeginInfo VulkanInitRenderPassBeginInfo(RenderPass renderPass, Framebuffer framebuffer, Scissor scissor, const ClearValue* clearValues, uint32_t clearValueCount)
	{
		ASSERT_HANDLE_SIZE(ClearValue, VkClearValue);
		VkClearValue* vulkanClearValues = (VkClearValue*)clearValues;

		RenderPassBeginInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.renderPass = renderPass.VkHandle;
		data.VkObject.framebuffer = framebuffer.VkHandle;
		data.VkObject.renderArea = scissor.VkObject;
		data.VkObject.pClearValues = vulkanClearValues;
		data.VkObject.clearValueCount = clearValueCount;
		return data;
	}

	inline PresentInfo VulkanInitPresentInfo(const Swapchain* swapchains, const uint32_t* imageIndices, uint32_t swapchainCount, const Semaphore* waitSemaphores, uint32_t waitCount)
	{
		ASSERT_HANDLE_SIZE(Swapchain, VkSwapchainKHR);
		ASSERT_HANDLE_SIZE(Semaphore, VkSemaphore);
		VkSwapchainKHR* vulkanSwapchains = (VkSwapchainKHR*)swapchains;
		VkSemaphore* vulkanSemaphores = (VkSemaphore*)waitSemaphores;


		PresentInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		data.VkObject.pNext = nullptr;
		data.VkObject.pSwapchains = vulkanSwapchains;
		data.VkObject.pImageIndices = imageIndices;
		data.VkObject.swapchainCount = swapchainCount;
		data.VkObject.pWaitSemaphores = vulkanSemaphores;
		data.VkObject.waitSemaphoreCount = waitCount;
		data.VkObject.pResults = nullptr;
		return data;
	}

	inline SemaphoreTimelineInfo VulkanInitSemaphoreTimelineInfo(uint64_t initialValue, SemaphoreType type)
	{
		SemaphoreTimelineInfo data;
		data.VkObject.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
		data.VkObject.pNext = nullptr;
		data.VkObject.initialValue = initialValue;
		data.VkObject.semaphoreType = toVkSemaphoreType(type);
		return data;
	}

#pragma endregion

#pragma region command_conversion

	struct VulkanContext
	{
		PLTF::Library VulkanDll;

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
		PFN_vkWaitSemaphores vkWaitSemaphores;

	} VkContext;


	VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		//ignored warning to use VK_EXT_debug_utils
		if (pCallbackData->messageIdNumber == 0x822806fa) {
			return VK_FALSE;
		}

		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: std::cerr << "VkError: " << pCallbackData->pMessage << '\n'; break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: std::cout << "VkWarning: " << pCallbackData->pMessage << '\n'; break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: std::cout << "VkInfo: " << pCallbackData->pMessage << '\n'; break;
		default: break; //std::cout << "VkVerbose: " << pCallbackData->pMessage << '\n'; break;
		}

		return VK_FALSE;
	}


	inline void VulkanInitialize(API api)
	{
		VkContext.VulkanDll.Load(L"vulkan-1.dll", "");
		VkContext.vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)VkContext.VulkanDll.GetFunction("vkGetInstanceProcAddr");
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
		VkContext.VulkanVersion &= (~0xFFF); //remove patch version

		//TODO: remove?
		VkContext.VulkanVersion = VK_MAKE_VERSION(1,2,0);
		
		//std::cout	<< VK_VERSION_MAJOR(VkContext.VulkanVersion) << "." 
		//			<< VK_VERSION_MINOR(VkContext.VulkanVersion) << "." 
		//			<< VK_VERSION_PATCH(VkContext.VulkanVersion) << "\n";
			
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
		
		VkPhysicalDeviceTimelineSemaphoreFeatures timelineFeatures;
		timelineFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
		timelineFeatures.pNext = nullptr;
		timelineFeatures.timelineSemaphore = VK_TRUE;
		
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
		deviceInfo.pNext = &timelineFeatures;
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
		INIT_DEV_FUNC(vkWaitSemaphores);

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

	inline void VulkanGetRenderQueue(Queue& queue, uint32_t& index)
	{
		queue.VkHandle = VkContext.RenderQueue;
		index = VkContext.RenderQueueIndex;
	}

	inline void VulkanGetTransferQueue(Queue& queue, uint32_t& index)
	{
		queue.VkHandle = VkContext.TransferQueue;
		index = VkContext.TransferQueueIndex;
	}

	inline void VulkanCreateBuffer(Buffer& handle, const BufferCreateInfo& createInfo)
	{
		VK_VALIDATE(vmaCreateBuffer(VkContext.MemoryAllocator, &createInfo.VkObject.BufferInfo, &createInfo.VkObject.AllocInfo, &handle.VkHandle.Buffer, &handle.VkHandle.Allocation, nullptr))
	}

	inline void VulkanDestroyBuffer(Buffer handle)
	{
		vmaDestroyBuffer(VkContext.MemoryAllocator, handle.VkHandle.Buffer, handle.VkHandle.Allocation);
	}

	inline void VulkanUploadMemory(Buffer dstBuffer, MemoryCopyData* copyData, uint32_t count)
	{
		void* deviceMemory;
		VK_VALIDATE(vmaMapMemory(VkContext.MemoryAllocator, dstBuffer.VkHandle.Allocation, &deviceMemory))
		for (uint32_t i = 0; i < count; i++) {
			memcpy((char*)deviceMemory + copyData[i].VkObject.DstOffset, copyData[i].VkObject.Data, copyData[i].VkObject.Size);
		}
		vmaUnmapMemory(VkContext.MemoryAllocator, dstBuffer.VkHandle.Allocation);
	}

	inline void VulkanCreateImage(Image& handle, const ImageCreateInfo& createInfo)
	{
		VK_VALIDATE(vmaCreateImage(VkContext.MemoryAllocator, &createInfo.VkObject.ImageInfo, &createInfo.VkObject.AllocInfo, &handle.VkHandle.Image, &handle.VkHandle.Allocation, nullptr))
	}

	inline void VulkanDestroyImage(Image handle)
	{
		vmaDestroyImage(VkContext.MemoryAllocator, handle.VkHandle.Image, handle.VkHandle.Allocation);
	}

	inline void VulkanCreateImageView(ImageView& handle, const ImageViewCreateInfo& createInfo)
	{
		VK_VALIDATE(VkContext.vkCreateImageView(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyImageView(ImageView handle)
	{
		VkContext.vkDestroyImageView(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateCmdPool(CmdPool& handle, const CmdPoolCreateInfo& createInfo)
	{
		VK_VALIDATE(VkContext.vkCreateCommandPool(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyCmdPool(CmdPool handle)
	{
		VkContext.vkDestroyCommandPool(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanResetCmdPool(CmdPool handle)
	{
		VK_VALIDATE(VkContext.vkResetCommandPool(VkContext.LogicalDevice, handle.VkHandle, 0))
	}

	inline void VulkanCreateCmdLists(CmdList* cmdLists, const CmdListsCreateInfo& createInfo)
	{
		ASSERT_HANDLE_SIZE(CmdList, VkCommandBuffer);
		VkCommandBuffer* vulkanCmdLists = (VkCommandBuffer*)cmdLists;

		VK_VALIDATE(VkContext.vkAllocateCommandBuffers(VkContext.LogicalDevice, &createInfo.VkObject, vulkanCmdLists))
	}

	inline void VulkanBeginRecording(CmdList cmdList, const BeginRecordingInfo& beginInfo)
	{
		VK_VALIDATE(VkContext.vkBeginCommandBuffer(cmdList.VkHandle, &beginInfo.VkObject.BeginInfo))
	}

	inline void VulkanStopRecording(CmdList cmdList)
	{
		VK_VALIDATE(VkContext.vkEndCommandBuffer(cmdList.VkHandle))
	}

	inline void VulkanSubmitCmdLists(Queue queue, const SubmitInfo* submitInfos, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(SubmitInfo, VkSubmitInfo);
		VkSubmitInfo* vulkanSubmitInfo = (VkSubmitInfo*)submitInfos;

		VK_VALIDATE(VkContext.vkQueueSubmit(queue.VkHandle, count, vulkanSubmitInfo, nullptr))
	}

	inline void VulkanResetCmdList(CmdList cmdList, bool releaseResources)
	{
		VK_VALIDATE(VkContext.vkResetCommandBuffer(cmdList.VkHandle, releaseResources))
	}

	inline void VulkanCreateDescriptorPool(DescriptorPool& handle, const DescriptorPoolCreateInfo& createInfo)
	{
		VK_VALIDATE(VkContext.vkCreateDescriptorPool(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyDescriptorPool(DescriptorPool handle)
	{
		VkContext.vkDestroyDescriptorPool(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateDescriptorLayout(DescriptorLayout& handle, const DescriptorLayoutCreateInfo& createInfo)
	{
		VK_VALIDATE(VkContext.vkCreateDescriptorSetLayout(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyDescriptorLayout(DescriptorLayout handle)
	{
		VkContext.vkDestroyDescriptorSetLayout(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateDescriptorSets(DescriptorSet* handles, const DescriptorSetsCreateInfo& createInfo)
	{
		ASSERT_HANDLE_SIZE(DescriptorSet, VkDescriptorSet);
		VkDescriptorSet* vulkanHandles = (VkDescriptorSet*)handles;

		VK_VALIDATE(VkContext.vkAllocateDescriptorSets(VkContext.LogicalDevice, &createInfo.VkObject, vulkanHandles))
	}

	inline void VulkanWriteDescriptorSet(DescriptorWriteData* writes, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(DescriptorWriteData, VkWriteDescriptorSet);
		VkWriteDescriptorSet* vulkanWrites = (VkWriteDescriptorSet*)writes;

		VkContext.vkUpdateDescriptorSets(VkContext.LogicalDevice, count, vulkanWrites, 0, nullptr);
	}

	inline void VulkanCreateFramebuffer(Framebuffer& handle, const FramebufferCreateInfo& createInfo)
	{
		VK_VALIDATE(VkContext.vkCreateFramebuffer(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyFramebuffer(Framebuffer handle)
	{
		VkContext.vkDestroyFramebuffer(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateRenderPass(RenderPass& handle, const RenderPassCreateInfo& createInfo)
	{
		VK_VALIDATE(VkContext.vkCreateRenderPass(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyRenderPass(RenderPass handle)
	{
		VkContext.vkDestroyRenderPass(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateShaderCompiler(ShaderCompiler& handle)
	{
		handle.VkHandle = shaderc_compiler_initialize();
		VkContext.CompilerOptions = shaderc_compile_options_initialize();
		shaderc_compile_options_set_source_language(VkContext.CompilerOptions, shaderc_source_language_glsl);
		shaderc_compile_options_set_optimization_level(VkContext.CompilerOptions, shaderc_optimization_level_performance);
	}

	inline void VulkanDestroyShaderCompiler(ShaderCompiler handle)
	{
		shaderc_compile_options_release(VkContext.CompilerOptions);
		shaderc_compiler_release(handle.VkHandle);
	}

	inline void VulkanCreateShader(Shader& handle, ShaderCompiler compiler, ShaderStageFlags stage, const char* code, uint32_t size)
	{
		shaderc_compilation_result_t result = shaderc_compile_into_spv(compiler.VkHandle, code, size,
												toShadercShaderKind(stage), "File", "main", VkContext.CompilerOptions);

		if (shaderc_result_get_compilation_status(result) != shaderc_compilation_status_success) {
			std::cout << shaderc_result_get_error_message(result) << "\n";
			verify(false, "Shader compilation failed.")
		}

		VkShaderModuleCreateInfo moduleCreateInfo;
		moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		moduleCreateInfo.pNext = nullptr;
		moduleCreateInfo.flags = 0;
		moduleCreateInfo.codeSize = shaderc_result_get_length(result);
		moduleCreateInfo.pCode = (uint32_t*)shaderc_result_get_bytes(result);

		VK_VALIDATE(VkContext.vkCreateShaderModule(VkContext.LogicalDevice, &moduleCreateInfo, nullptr, &handle.VkHandle))

		shaderc_result_release(result);
	}

	inline void VulkanDestroyShader(Shader handle)
	{
		VkContext.vkDestroyShaderModule(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateSampler(Sampler& handle, const SamplerCreateInfo& createInfo)
	{
		VK_VALIDATE(VkContext.vkCreateSampler(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroySampler(Sampler handle)
	{
		VkContext.vkDestroySampler(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateSemaphore(Semaphore& handle, const SemaphoreTimelineInfo* timelineInfo)
	{
		VkSemaphoreCreateInfo createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		createInfo.pNext = &timelineInfo->VkObject;
		createInfo.flags = 0;

		VK_VALIDATE(VkContext.vkCreateSemaphore(VkContext.LogicalDevice, &createInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroySemaphore(Semaphore handle)	
	{
		VkContext.vkDestroySemaphore(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanWaitSemaphores(const Semaphore* semaphores, const uint64_t* values, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(Semaphore, VkSemaphore);
		VkSemaphore* vulkanSemaphores = (VkSemaphore*)semaphores;

		VkSemaphoreWaitInfo info;
		info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
		info.pNext = nullptr;
		info.flags = 0;
		info.pSemaphores = vulkanSemaphores;
		info.pValues = values;
		info.semaphoreCount = count;

		VkContext.vkWaitSemaphores(VkContext.LogicalDevice, &info, UINT64_MAX);
	}

	inline void VulkanCreateSurface(Surface& handle, const void* window, const void* module, const void* monitor)
	{
		VkWin32SurfaceCreateInfoKHR surfaceInfo;
		surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.pNext = nullptr;
		surfaceInfo.flags = 0;
		surfaceInfo.hinstance = (HINSTANCE)module;
		surfaceInfo.hwnd = (HWND)window;

		VK_VALIDATE(VkContext.vkCreateWin32SurfaceKHR(VkContext.Instance, &surfaceInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroySurface(Surface handle)
	{
		VkContext.vkDestroySurfaceKHR(VkContext.Instance, handle.VkHandle, nullptr);
	}

	inline void VulkanCreateSwapchain(Swapchain& handle, const Swapchain* old, Surface surface, Queue* presentQueue, uint32_t* layers, uint32_t* imageCount, uint32_t* width, uint32_t* height)
	{
		VkSwapchainCreateInfoKHR swapchainInfo;

		uint32_t formatCount;
		VK_VALIDATE(VkContext.vkGetPhysicalDeviceSurfaceFormatsKHR(VkContext.PhysicalDevice, surface.VkHandle, &formatCount, nullptr))

		VkSurfaceFormatKHR* surfaceFormats = new VkSurfaceFormatKHR[formatCount];
		VK_VALIDATE(VkContext.vkGetPhysicalDeviceSurfaceFormatsKHR(VkContext.PhysicalDevice, surface.VkHandle, &formatCount, surfaceFormats))

		if (surfaceFormats[0].format == VK_FORMAT_UNDEFINED) {
			swapchainInfo.imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
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

		for (int32_t x = 5; x >= 0; x--) {
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

		for (int32_t i = 3; i >= 0; i--) {
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
		swapchainInfo.flags = 0;
		swapchainInfo.surface = surface.VkHandle;
		swapchainInfo.minImageCount = *imageCount;
		swapchainInfo.imageExtent.width = *width;
		swapchainInfo.imageExtent.height = *height;
		swapchainInfo.preTransform = capabilities.currentTransform;
		swapchainInfo.imageArrayLayers = *layers;
		swapchainInfo.oldSwapchain = old == nullptr ? nullptr : old->VkHandle;
		swapchainInfo.clipped = true;
		swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VK_VALIDATE(VkContext.vkCreateSwapchainKHR(VkContext.LogicalDevice, &swapchainInfo, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroySwapchain(Swapchain handle)
	{
		VkContext.vkDestroySwapchainKHR(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanGetSwapchainImages(Image* images, uint32_t count, Swapchain swapchain)
	{
		uint32_t imageCount;
		VK_VALIDATE(VkContext.vkGetSwapchainImagesKHR(VkContext.LogicalDevice, swapchain.VkHandle, &imageCount, nullptr))
		validate(count == imageCount)

		VkImage* swapchainImages = new VkImage[imageCount];
		VK_VALIDATE(VkContext.vkGetSwapchainImagesKHR(VkContext.LogicalDevice, swapchain.VkHandle, &imageCount, swapchainImages))

		for (uint32_t i = 0; i < imageCount; i++) {
			images[i].VkHandle.Image = swapchainImages[i];
		}
		
		delete[] swapchainImages;
	}

	inline void VulkanGetNextImage(Swapchain swapchain, Semaphore signalSemaphore, uint32_t* imageIndex)
	{
		VkContext.vkAcquireNextImageKHR(
			VkContext.LogicalDevice,
			swapchain.VkHandle,
			UINT64_MAX,
			signalSemaphore.VkHandle,
			nullptr,
			imageIndex);
	}

	inline void VulkanPresentImage(Queue presentQueue, const PresentInfo& presentInfo)
	{
		VkContext.vkQueuePresentKHR(presentQueue.VkHandle, &presentInfo.VkObject);
	}

	inline void VulkanCreateGraphicsPipelines(Pipeline* handles, const GraphicsPipelineCreateInfo* createInfos, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(VkGraphicsPipelineCreateInfo, GraphicsPipelineCreateInfo);
		ASSERT_HANDLE_SIZE(Pipeline, VkPipeline);
		VkGraphicsPipelineCreateInfo* vulkanCreateInfos = (VkGraphicsPipelineCreateInfo*)createInfos;
		VkPipeline* vulkanHandles = (VkPipeline*)handles;

		VK_VALIDATE(VkContext.vkCreateGraphicsPipelines(VkContext.LogicalDevice, VK_NULL_HANDLE, count, vulkanCreateInfos, nullptr, vulkanHandles))
	}

	inline void VulkanDestroyPipeline(Pipeline handle)
	{
		VkContext.vkDestroyPipeline(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCreatePipelineLayout(PipelineLayout& handle, const PipelineLayoutCreateInfo& createInfo)
	{
		VK_VALIDATE(VkContext.vkCreatePipelineLayout(VkContext.LogicalDevice, &createInfo.VkObject, nullptr, &handle.VkHandle))
	}

	inline void VulkanDestroyPipelineLayout(PipelineLayout handle)
	{
		VkContext.vkDestroyPipelineLayout(VkContext.LogicalDevice, handle.VkHandle, nullptr);
	}

	inline void VulkanCopyBuffer(CmdList cmdList, Buffer srcBuffer, Buffer dstBuffer, const BufferCopyData* copyData, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(BufferCopyData, VkBufferCopy);
		VkBufferCopy* vulkanCopyData = (VkBufferCopy*)copyData;

		VkContext.vkCmdCopyBuffer(cmdList.VkHandle, srcBuffer.VkHandle.Buffer, dstBuffer.VkHandle.Buffer, count, vulkanCopyData);
	}

	inline void VulkanCopyBufferToImage(CmdList cmdList, Buffer srcBuffer, Image dstImage, ImageLayout currentLayout, const BufferImageCopyData* copyData, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(BufferImageCopyData, VkBufferImageCopy);
		VkBufferImageCopy* vulkanCopyData = (VkBufferImageCopy*)copyData;

		VkContext.vkCmdCopyBufferToImage(cmdList.VkHandle, srcBuffer.VkHandle.Buffer, dstImage.VkHandle.Image, toVkImageLayout(currentLayout), count, vulkanCopyData);
	}

	inline void VulkanExecuteCmdLists(CmdList cmdList, const CmdList* cmdLists, uint32_t count)
	{
		ASSERT_HANDLE_SIZE(CmdList, VkCommandBuffer);
		VkCommandBuffer* vulkanCmdLists = (VkCommandBuffer*)cmdLists;

		VkContext.vkCmdExecuteCommands(cmdList.VkHandle, count, vulkanCmdLists);
	}

	inline void VulkanBeginRenderPass(CmdList cmdList, const RenderPassBeginInfo& beginInfo, bool inlineCommands)
	{
		VkContext.vkCmdBeginRenderPass(cmdList.VkHandle, &beginInfo.VkObject, (inlineCommands ? VK_SUBPASS_CONTENTS_INLINE : VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS));
	}

	inline void VulkanEndRenderPass(CmdList cmdList)
	{
		VkContext.vkCmdEndRenderPass(cmdList.VkHandle);
	}

	inline void VulkanBindViewports(CmdList cmdList, const Viewport* viewports, uint32_t viewportCount, uint32_t startIndex)
	{
		ASSERT_HANDLE_SIZE(Viewport, VkViewport);
		VkViewport* vulkanViewports = (VkViewport*)viewports;

		VkContext.vkCmdSetViewport(cmdList.VkHandle, startIndex, viewportCount, vulkanViewports);
	}

	inline void VulkanBindScissors(CmdList cmdList, const Scissor* scissors, uint32_t scissorCount, uint32_t startIndex)
	{
		ASSERT_HANDLE_SIZE(Scissor, VkRect2D);
		VkRect2D* vulkanScissors = (VkRect2D*)scissors;

		VkContext.vkCmdSetScissor(cmdList.VkHandle, startIndex, scissorCount, vulkanScissors);
	}

	inline void VulkanBindPipeline(CmdList cmdList, Pipeline pipeline, PipelineBindPoint bindPoint)
	{
		VkContext.vkCmdBindPipeline(cmdList.VkHandle, toVkPipelineBindPoint(bindPoint), pipeline.VkHandle);
	}

	inline void VulkanBindVertexBuffer(CmdList cmdList, Buffer vertexBuffer, uint32_t binding, uint32_t bindingCount, uint64_t offset)
	{
		VkContext.vkCmdBindVertexBuffers(cmdList.VkHandle, binding, bindingCount, &vertexBuffer.VkHandle.Buffer, &offset);
	}

	inline void VulkanBindIndexBuffer(CmdList cmdList, Buffer indexBuffer, IndexType type, uint64_t offset)
	{
		VkContext.vkCmdBindIndexBuffer(cmdList.VkHandle, indexBuffer.VkHandle.Buffer, offset, toVkIndexType(type));
	}

	inline void VulkanBindDescriptorSets(CmdList cmdList, PipelineLayout layout, const DescriptorSet* sets, uint32_t descriptorSetCount, uint32_t startIndex, PipelineBindPoint bindPoint)
	{
		ASSERT_HANDLE_SIZE(DescriptorSet, VkDescriptorSet);
		VkDescriptorSet* vulkanSets = (VkDescriptorSet*)sets;

		VkContext.vkCmdBindDescriptorSets(cmdList.VkHandle, toVkPipelineBindPoint(bindPoint), layout.VkHandle, startIndex, descriptorSetCount, vulkanSets, 0, 0);
	}

	inline void VulkanDraw(CmdList cmdList, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
	{
		VkContext.vkCmdDraw(cmdList.VkHandle, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	inline void VulkanDrawIndexed(CmdList cmdList, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, uint32_t vertexOffset, uint32_t firstInstance)
	{
		VkContext.vkCmdDrawIndexed(cmdList.VkHandle, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
	}

#pragma endregion
}