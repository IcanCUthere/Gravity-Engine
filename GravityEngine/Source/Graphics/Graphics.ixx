module;
#include "Core/DebugUtils.h"
#include <shaderc/shaderc.h>

export module Graphics;
import "MemoryAllocator.h";
import stdlib;

#define DEFINE_GFX_FUNCTION(name, parameters, parameterNames, extra) \
inline void Vulkan##name##parameters; \
/*inline void DirectX12##name##parameters;*/ \
/*inline void OpenGL##name##parameters;*/ \
export inline void name##parameters \
{ \
	extra \
	switch(UsedAPI) \
	{ \
		case API::Vulkan: Vulkan##name##parameterNames; break; \
		/*case EAPI::DirectX12: DirectX12##name##parameterNames; break;*/ \
		/*case EAPI::OpenGL: OpenGL##name##parameterNames; break;*/ \
		default: THROW_ERROR(); \
	} \
}

#define DEFINE_GFX_UNION(name, vkName, dx12Name, glName, parameters, parameterNames) \
export union name \
{\
	vkName VkObject; \
	/*dx12Name DxObject;*/ \
	/*glName GlObject;*/ \
};\
inline name VulkanInit##name##parameters; \
/*inline returnType DirectX12##name##parameters;*/ \
/*inline returnType OpenGL##name##parameters;*/ \
export inline name Init##name##parameters \
{ \
	switch(UsedAPI) \
	{ \
		case API::Vulkan: return VulkanInit##name##parameterNames; \
		/*case EAPI::DirectX12: return DirectX12Init##name##parameterNames;*/ \
		/*case EAPI::OpenGL: return OpenGLInit##name##parameterNames;*/ \
		default: THROW_ERROR(); return name{}; \
	} \
}

#define DEF_ENUM_OPS(name) \
	export inline name operator|(const name& o1, const name& o2) \
	{ \
		return (name)((uint32_t)o1 | (uint32_t)o2);\
	}

namespace GFX
{
	export enum class API
	{
		Vulkan,
		DirectX12,
		OpenGL
	} UsedAPI;

	export union Buffer
	{
		struct {
			VkBuffer Buffer;
			VmaAllocation Allocation;
		} VkHandle;
	};

	export union Image
	{
		struct {
			VkImage Image;
			VmaAllocation Allocation;
		} VkHandle;
	};

	export union CmdPool
	{
		VkCommandPool VkHandle;
	};

	export union CmdList
	{
		VkCommandBuffer VkHandle;
	};

	export union RenderPass
	{
		VkRenderPass VkHandle;
	};

	export union Framebuffer
	{
		VkFramebuffer VkHandle;
	};

	export union Queue
	{
		struct {
			VkQueue Queue;
			uint32_t Index;
		} VkHandle;
	};

	export union Semaphore
	{
		VkSemaphore VkHandle;
	};

	export union DescriptorPool
	{
		VkDescriptorPool VkHandle;
	};

	export union DescriptorLayout
	{
		VkDescriptorSetLayout VkHandle;
	};

	export union DescriptorSet
	{
		VkDescriptorSet VkHandle;
	};

	export union ImageView
	{
		VkImageView VkHandle;
	};

	export union Sampler
	{
		VkSampler VkHandle;
	};

	export union Shader
	{
		VkShaderModule VkHandle;
	};

	export union ShaderCompiler
	{
		shaderc_compiler_t VkHandle;
	};

	export union Surface
	{
		VkSurfaceKHR VkHandle;
	};

	export union Swapchain
	{
		VkSwapchainKHR VkHandle;
	};

	export union Pipeline
	{
		VkPipeline VkHandle;
	};

	export union PipelineLayout
	{
		VkPipelineLayout VkHandle;
	};

	export enum Format
	{
		FORMAT_UNDEFINED,
		FORMAT_R8_UNORM,
		FORMAT_R8_SNORM,
		FORMAT_R8_USCALED,
		FORMAT_R8_SSCALED,
		FORMAT_R8_UINT,
		FORMAT_R8_SINT,
		FORMAT_R8_SRGB,
		FORMAT_R8G8_UNORM,
		FORMAT_R8G8_SNORM,
		FORMAT_R8G8_USCALED,
		FORMAT_R8G8_SSCALED,
		FORMAT_R8G8_UINT,
		FORMAT_R8G8_SINT,
		FORMAT_R8G8_SRGB,
		FORMAT_R8G8B8_UNORM,
		FORMAT_R8G8B8_SNORM,
		FORMAT_R8G8B8_USCALED,
		FORMAT_R8G8B8_SSCALED,
		FORMAT_R8G8B8_UINT,
		FORMAT_R8G8B8_SINT,
		FORMAT_R8G8B8_SRGB,
		FORMAT_B8G8R8_UNORM,
		FORMAT_B8G8R8_SNORM,
		FORMAT_B8G8R8_USCALED,
		FORMAT_B8G8R8_SSCALED,
		FORMAT_B8G8R8_UINT,
		FORMAT_B8G8R8_SINT,
		FORMAT_B8G8R8_SRGB,
		FORMAT_R8G8B8A8_UNORM,
		FORMAT_R8G8B8A8_SNORM,
		FORMAT_R8G8B8A8_USCALED,
		FORMAT_R8G8B8A8_SSCALED,
		FORMAT_R8G8B8A8_UINT,
		FORMAT_R8G8B8A8_SINT,
		FORMAT_R8G8B8A8_SRGB,
		FORMAT_B8G8R8A8_UNORM,
		FORMAT_B8G8R8A8_SNORM,
		FORMAT_B8G8R8A8_USCALED,
		FORMAT_B8G8R8A8_SSCALED,
		FORMAT_B8G8R8A8_UINT,
		FORMAT_B8G8R8A8_SINT,
		FORMAT_B8G8R8A8_SRGB,
		FORMAT_R16_UNORM,
		FORMAT_R16_SNORM,
		FORMAT_R16_USCALED,
		FORMAT_R16_SSCALED,
		FORMAT_R16_UINT,
		FORMAT_R16_SINT,
		FORMAT_R16_SFLOAT,
		FORMAT_R16G16_UNORM,
		FORMAT_R16G16_SNORM,
		FORMAT_R16G16_USCALED,
		FORMAT_R16G16_SSCALED,
		FORMAT_R16G16_UINT,
		FORMAT_R16G16_SINT,
		FORMAT_R16G16_SFLOAT,
		FORMAT_R16G16B16_UNORM,
		FORMAT_R16G16B16_SNORM,
		FORMAT_R16G16B16_USCALED,
		FORMAT_R16G16B16_SSCALED,
		FORMAT_R16G16B16_UINT,
		FORMAT_R16G16B16_SINT,
		FORMAT_R16G16B16_SFLOAT,
		FORMAT_R16G16B16A16_UNORM,
		FORMAT_R16G16B16A16_SNORM,
		FORMAT_R16G16B16A16_USCALED,
		FORMAT_R16G16B16A16_SSCALED,
		FORMAT_R16G16B16A16_UINT,
		FORMAT_R16G16B16A16_SINT,
		FORMAT_R16G16B16A16_SFLOAT,
		FORMAT_R32_UINT,
		FORMAT_R32_SINT,
		FORMAT_R32_SFLOAT,
		FORMAT_R32G32_UINT,
		FORMAT_R32G32_SINT,
		FORMAT_R32G32_SFLOAT,
		FORMAT_R32G32B32_UINT,
		FORMAT_R32G32B32_SINT,
		FORMAT_R32G32B32_SFLOAT,
		FORMAT_R32G32B32A32_UINT,
		FORMAT_R32G32B32A32_SINT,
		FORMAT_R32G32B32A32_SFLOAT,
		FORMAT_R64_UINT,
		FORMAT_R64_SINT,
		FORMAT_R64_SFLOAT,
		FORMAT_R64G64_UINT,
		FORMAT_R64G64_SINT,
		FORMAT_R64G64_SFLOAT,
		FORMAT_R64G64B64_UINT,
		FORMAT_R64G64B64_SINT,
		FORMAT_R64G64B64_SFLOAT,
		FORMAT_R64G64B64A64_UINT,
		FORMAT_R64G64B64A64_SINT,
		FORMAT_R64G64B64A64_SFLOAT,
		FORMAT_D16_UNORM,
		FORMAT_D32_SFLOAT,
		FORMAT_S8_UINT,
		FORMAT_D16_UNORM_S8_UINT,
		FORMAT_D24_UNORM_S8_UINT,
		FORMAT_D32_SFLOAT_S8_UINT,
	};

	export enum MemoryUsage
	{
		MEMORY_USAGE_GPU_ONLY,
		MEMORY_USAGE_CPU_ONLY,
		MEMORY_USAGE_CPU_TO_GPU,
		MEMORY_USAGE_GPU_TO_CPU,
		MEMORY_USAGE_CPU_COPY,
		MEMORY_USAGE_AUTO,
		MEMORY_USAGE_AUTO_PREFER_DEVICE,
		MEMORY_USAGE_AUTO_PREFER_HOST,
	};

	export enum CmdListLevel
	{
		CMD_LIST_LEVEL_PRIMARY,
		CMD_LIST_LEVEL_SECONDARY,
	};

	export enum DescriptorType
	{
		DESCRIPTOR_TYPE_SAMPLER,
		DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		DESCRIPTOR_TYPE_SAMPLED_IMAGE,
		DESCRIPTOR_TYPE_STORAGE_IMAGE,
		DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
		DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
		DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		DESCRIPTOR_TYPE_STORAGE_BUFFER,
		DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
		DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
		DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
	};

	export enum ImageLayout
	{
		IMAGE_LAYOUT_UNDEFINED,
		IMAGE_LAYOUT_GENERAL,
		IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
		IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
		IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		IMAGE_LAYOUT_PREINITIALIZED,
		IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
		IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
		IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
		IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL,
		IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL,
		IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL,
		IMAGE_LAYOUT_PRESENT_SRC,
	};

	export enum ImageType
	{
		IMAGE_TYPE_1D,
		IMAGE_TYPE_2D,
		IMAGE_TYPE_3D,
	};

	export enum ImageTiling
	{
		IMAGE_TILING_OPTIMAL,
		IMAGE_TILING_LINEAR,
	};

	export enum ImageViewType
	{
		IMAGE_VIEW_TYPE_1D,
		IMAGE_VIEW_TYPE_2D,
		IMAGE_VIEW_TYPE_3D,
	};

	export enum LoadOp
	{
		LOAD_OP_LOAD,
		LOAD_OP_CLEAR,
		LOAD_OP_DONT_CARE,
	};

	export enum StoreOp
	{
		STORE_OP_STORE,
		STORE_OP_DONT_CARE,
	};

	export enum PipelineBindPoint
	{
		PIPELINE_BIND_POINT_GRAPHICS,
		PIPELINE_BIND_POINT_COMPUTE,
		PIPELINE_BIND_POINT_RAY_TRACING,
	};

	export enum Filter
	{
		FILTER_NEAREST,
		FILTER_LINEAR,
		FILTER_CUBIC_IMG,
	};

	export enum AddressMode
	{
		ADDRESS_MODE_REPEAT,
		ADDRESS_MODE_MIRRORED_REPEAT,
		ADDRESS_MODE_CLAMP_TO_EDGE,
		ADDRESS_MODE_CLAMP_TO_BORDER,
		ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE,
	};

	export enum MipmapMode
	{
		MIPMAP_MODE_NEAREST,
		MIPMAP_MODE_LINEAR,
	};

	export enum CompareOp
	{
		COMPARE_OP_NEVER,
		COMPARE_OP_LESS,
		COMPARE_OP_EQUAL,
		COMPARE_OP_LESS_OR_EQUAL,
		COMPARE_OP_GREATER,
		COMPARE_OP_NOT_EQUAL,
		COMPARE_OP_GREATER_OR_EQUAL,
		COMPARE_OP_ALWAYS,
	};

	export enum IndexType
	{
		INDEX_TYPE_UINT16,
		INDEX_TYPE_UINT32,
	};

	export enum PrimitiveTopology
	{
		PRIMITIVE_TOPOLOGY_POINT_LIST,
		PRIMITIVE_TOPOLOGY_LINE_LIST,
		PRIMITIVE_TOPOLOGY_LINE_STRIP,
		PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
		PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
		PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
		PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
		PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
		PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
		PRIMITIVE_TOPOLOGY_PATCH_LIST,
	};

	export enum PolygonMode
	{
		POLYGON_MODE_FILL,
		POLYGON_MODE_LINE,
		POLYGON_MODE_POINT,
	};

	export enum FrontFace
	{
		FRONT_FACE_COUNTER_CLOCKWISE,
		FRONT_FACE_CLOCKWISE,
	};

	export enum StencilOp
	{
		STENCIL_OP_KEEP,
		STENCIL_OP_ZERO,
		STENCIL_OP_REPLACE,
		STENCIL_OP_INCREMENT_AND_CLAMP,
		STENCIL_OP_DECREMENT_AND_CLAMP,
		STENCIL_OP_INVERT,
		STENCIL_OP_INCREMENT_AND_WRAP,
		STENCIL_OP_DECREMENT_AND_WRAP,
	};

	export enum LogicOp
	{
		LOGIC_OP_CLEAR,
		LOGIC_OP_AND,
		LOGIC_OP_AND_REVERSE,
		LOGIC_OP_COPY,
		LOGIC_OP_AND_INVERTED,
		LOGIC_OP_NO_OP,
		LOGIC_OP_XOR,
		LOGIC_OP_OR,
		LOGIC_OP_NOR,
		LOGIC_OP_EQUIVALENT,
		LOGIC_OP_INVERT,
		LOGIC_OP_OR_REVERSE,
		LOGIC_OP_COPY_INVERTED,
		LOGIC_OP_OR_INVERTED,
		LOGIC_OP_NAND,
		LOGIC_OP_SET,
	};

	export enum BlendOp
	{
		BLEND_OP_ADD,
		BLEND_OP_SUBTRACT,
		BLEND_OP_REVERSE_SUBTRACT,
		BLEND_OP_MIN,
		BLEND_OP_MAX,
	};

	export enum BlendFactor
	{
		BLEND_FACTOR_ZERO,
		BLEND_FACTOR_ONE,
		BLEND_FACTOR_SRC_COLOR,
		BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
		BLEND_FACTOR_DST_COLOR,
		BLEND_FACTOR_ONE_MINUS_DST_COLOR,
		BLEND_FACTOR_SRC_ALPHA,
		BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		BLEND_FACTOR_DST_ALPHA,
		BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
		BLEND_FACTOR_CONSTANT_COLOR,
		BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
		BLEND_FACTOR_CONSTANT_ALPHA,
		BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,
		BLEND_FACTOR_SRC_ALPHA_SATURATE,
		BLEND_FACTOR_SRC1_COLOR,
		BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
		BLEND_FACTOR_SRC1_ALPHA,
		BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,
	};

	export enum DynamicState
	{
		DYNAMIC_STATE_VIEWPORT,
		DYNAMIC_STATE_SCISSOR,
		DYNAMIC_STATE_LINE_WIDTH,
		DYNAMIC_STATE_DEPTH_BIAS,
		DYNAMIC_STATE_BLEND_CONSTANTS,
		DYNAMIC_STATE_DEPTH_BOUNDS,
		DYNAMIC_STATE_STENCIL_COMPARE_MASK,
		DYNAMIC_STATE_STENCIL_WRITE_MASK,
		DYNAMIC_STATE_STENCIL_REFERENCE,
	};

	export enum InputRate
	{
		INPUT_RATE_VERTEX,
		INPUT_RATE_INSTANCE,
	};

	export enum SemaphoreType
	{
		SEMAPHORE_TYPE_BINARY,
		SEMAPHORE_TYPE_TIMELINE
	};

	export enum PipelineStageFlags
	{
		PIPELINE_STAGE_NONE = 0,
		PIPELINE_STAGE_TOP_OF_PIPE_BIT = 0x00000001,
		PIPELINE_STAGE_DRAW_INDIRECT_BIT = 0x00000002,
		PIPELINE_STAGE_VERTEX_INPUT_BIT = 0x00000004,
		PIPELINE_STAGE_VERTEX_SHADER_BIT = 0x00000008,
		PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT = 0x00000010,
		PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT = 0x00000020,
		PIPELINE_STAGE_GEOMETRY_SHADER_BIT = 0x00000040,
		PIPELINE_STAGE_FRAGMENT_SHADER_BIT = 0x00000080,
		PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT = 0x00000100,
		PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT = 0x00000200,
		PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT = 0x00000400,
		PIPELINE_STAGE_COMPUTE_SHADER_BIT = 0x00000800,
		PIPELINE_STAGE_TRANSFER_BIT = 0x00001000,
		PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT = 0x00002000,
		PIPELINE_STAGE_HOST_BIT = 0x00004000,
		PIPELINE_STAGE_ALL_GRAPHICS_BIT = 0x00008000,
		PIPELINE_STAGE_ALL_COMMANDS_BIT = 0x00010000,
	};
	DEF_ENUM_OPS(PipelineStageFlags);

	export enum SampleCountFlags
	{
		SAMPLE_COUNT_NONE = 0,
		SAMPLE_COUNT_1_BIT = 0x00000001,
		SAMPLE_COUNT_2_BIT = 0x00000002,
		SAMPLE_COUNT_4_BIT = 0x00000004,
		SAMPLE_COUNT_8_BIT = 0x00000008,
		SAMPLE_COUNT_16_BIT = 0x00000010,
		SAMPLE_COUNT_32_BIT = 0x00000020,
		SAMPLE_COUNT_64_BIT = 0x00000040,
	};
	DEF_ENUM_OPS(SampleCountFlags);

	export enum BufferUsageFlags
	{
		BUFFER_USAGE_NONE = 0,
		BUFFER_USAGE_TRANSFER_SRC_BIT = 0x00000001,
		BUFFER_USAGE_TRANSFER_DST_BIT = 0x00000002,
		BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT = 0x00000004,
		BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT = 0x00000008,
		BUFFER_USAGE_UNIFORM_BUFFER_BIT = 0x00000010,
		BUFFER_USAGE_STORAGE_BUFFER_BIT = 0x00000020,
		BUFFER_USAGE_INDEX_BUFFER_BIT = 0x00000040,
		BUFFER_USAGE_VERTEX_BUFFER_BIT = 0x00000080,
		BUFFER_USAGE_INDIRECT_BUFFER_BIT = 0x00000100,
	};
	DEF_ENUM_OPS(BufferUsageFlags);

	export enum CmdListUsageFlags
	{
		CMD_LIST_USAGE_NONE = 0,
		CMD_LIST_USAGE_ONE_TIME_SUBMIT_BIT = 0x00000001,
		CMD_LIST_USAGE_RENDER_PASS_CONTINUE_BIT = 0x00000002,
		CMD_LIST_USAGE_SIMULTANEOUS_USE_BIT = 0x00000004,
	};
	DEF_ENUM_OPS(CmdListUsageFlags);

	export enum ImageUsageFlags
	{
		IMAGE_USAGE_NONE = 0,
		IMAGE_USAGE_TRANSFER_SRC_BIT = 0x00000001,
		IMAGE_USAGE_TRANSFER_DST_BIT = 0x00000002,
		IMAGE_USAGE_SAMPLED_BIT = 0x00000004,
		IMAGE_USAGE_STORAGE_BIT = 0x00000008,
		IMAGE_USAGE_COLOR_ATTACHMENT_BIT = 0x00000010,
		IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
		IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040,
		IMAGE_USAGE_INPUT_ATTACHMENT_BIT = 0x00000080,
	};
	DEF_ENUM_OPS(ImageUsageFlags);

	export enum ColorFlags
	{
		COLOR_COMPONENT_NONE = 0,
		COLOR_COMPONENT_R_BIT = 0x00000001,
		COLOR_COMPONENT_G_BIT = 0x00000002,
		COLOR_COMPONENT_B_BIT = 0x00000004,
		COLOR_COMPONENT_A_BIT = 0x00000008,
	};
	DEF_ENUM_OPS(ColorFlags);

	export enum CullModeFlags
	{
		CULL_MODE_NONE = 0,
		CULL_MODE_FRONT_BIT = 0x00000001,
		CULL_MODE_BACK_BIT = 0x00000002,
		CULL_MODE_FRONT_AND_BACK = 0x00000003,
	};
	DEF_ENUM_OPS(CullModeFlags);

	export enum AccessFlags
	{
		ACCESS_NONE = 0,
		ACCESS_INDIRECT_COMMAND_READ_BIT = 0x00000001,
		ACCESS_INDEX_READ_BIT = 0x00000002,
		ACCESS_VERTEX_ATTRIBUTE_READ_BIT = 0x00000004,
		ACCESS_UNIFORM_READ_BIT = 0x00000008,
		ACCESS_INPUT_ATTACHMENT_READ_BIT = 0x00000010,
		ACCESS_SHADER_READ_BIT = 0x00000020,
		ACCESS_SHADER_WRITE_BIT = 0x00000040,
		ACCESS_COLOR_ATTACHMENT_READ_BIT = 0x00000080,
		ACCESS_COLOR_ATTACHMENT_WRITE_BIT = 0x00000100,
		ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = 0x00000200,
		ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = 0x00000400,
		ACCESS_TRANSFER_READ_BIT = 0x00000800,
		ACCESS_TRANSFER_WRITE_BIT = 0x00001000,
		ACCESS_HOST_READ_BIT = 0x00002000,
		ACCESS_HOST_WRITE_BIT = 0x00004000,
		ACCESS_MEMORY_READ_BIT = 0x00008000,
		ACCESS_MEMORY_WRITE_BIT = 0x00010000,
	};
	DEF_ENUM_OPS(AccessFlags);

	export enum DependencyFlags
	{
		DEPENDENCY_NONE = 0,
		DEPENDENCY_BY_REGION_BIT = 0x00000001,
		DEPENDENCY_DEVICE_GROUP_BIT = 0x00000004,
		DEPENDENCY_VIEW_LOCAL_BIT = 0x00000002,
	};
	DEF_ENUM_OPS(DependencyFlags);

	export enum ShaderStageFlags
	{
		SHADER_STAGE_NONE = 0,
		SHADER_STAGE_VERTEX_BIT = 0x00000001,
		SHADER_STAGE_TESSELLATION_CONTROL_BIT = 0x00000002,
		SHADER_STAGE_TESSELLATION_EVALUATION_BIT = 0x00000004,
		SHADER_STAGE_GEOMETRY_BIT = 0x00000008,
		SHADER_STAGE_FRAGMENT_BIT = 0x00000010,
		SHADER_STAGE_COMPUTE_BIT = 0x00000020,
		SHADER_STAGE_ALL_GRAPHICS = 0x0000001F,
		SHADER_STAGE_ALL = 0x7FFFFFFF,
	};
	DEF_ENUM_OPS(ShaderStageFlags);

	export enum ImageAspectFlags
	{
		IMAGE_ASPECT_NONE = 0,
		IMAGE_ASPECT_COLOR_BIT = 0x00000001,
		IMAGE_ASPECT_DEPTH_BIT = 0x00000002,
		IMAGE_ASPECT_STENCIL_BIT = 0x00000004,
	};
	DEF_ENUM_OPS(ImageAspectFlags);




	DEFINE_GFX_UNION(MemoryCopyData, struct { void* Data; uint32_t DstOffset; uint32_t Size; }, NA, NA,
		(void* data, uint32_t dstOffset, uint32_t size),
		(data, dstOffset, size))

	DEFINE_GFX_UNION(Offset3D, VkOffset3D, NA, NA,
		(int32_t widht, int32_t height, int32_t depth),
		(widht, height, depth))

	DEFINE_GFX_UNION(Extent3D, VkExtent3D, NA, NA,
		(uint32_t x, uint32_t y, uint32_t z),
		(x, y, z))

	DEFINE_GFX_UNION(ClearValue, VkClearValue, NA, NA,
		(const float float32[4], const int32_t int32[4], const uint32_t uint32[4], float depth, uint32_t stencil),
		(float32, int32, uint32, depth, stencil))

	DEFINE_GFX_UNION(Scissor, VkRect2D, NA, NA,
		(uint32_t width, uint32_t height, int32_t x, int32_t y),
		(width, height, x, y))

	DEFINE_GFX_UNION(Viewport, VkViewport, NA, NA, 
		(float x, float y, float width, float height, float minDepth, float maxDepth),
		(x, y, width, height, minDepth, maxDepth))

	DEFINE_GFX_UNION(ImageSubresourceLayers, VkImageSubresourceLayers, NA, NA,
		(ImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t baseLayer, uint32_t layerCount),
		(aspectMask, mipLevel, baseLayer, layerCount))

	DEFINE_GFX_UNION(ImageSubresourceRange, VkImageSubresourceRange, NA, NA,
		(ImageAspectFlags aspectMask, uint32_t mipLevel, uint32_t levelCount, uint32_t baseLayer, uint32_t layerCount),
		(aspectMask, mipLevel, levelCount, baseLayer, layerCount))

	DEFINE_GFX_UNION(BufferCopyData, VkBufferCopy, NA, NA,
		(uint32_t srcOffset, uint32_t dstOffset, uint32_t size),
		(srcOffset, dstOffset, size))

	DEFINE_GFX_UNION(BufferImageCopyData, VkBufferImageCopy, NA, NA,
		(uint64_t srcOffset, uint32_t rowLength, uint32_t bufferImageHeight, Offset3D imageOffset, Extent3D imageExtent, const ImageSubresourceLayers& subresource),
		(srcOffset, rowLength, bufferImageHeight, imageOffset, imageExtent, subresource))

	DEFINE_GFX_UNION(DescriptorPoolSize, VkDescriptorPoolSize, NA, NA,
		(DescriptorType type, uint32_t count),
		(type, count))

	DEFINE_GFX_UNION(DescriptorLayoutBinding, VkDescriptorSetLayoutBinding, NA, NA,
		(uint32_t binding, DescriptorType type, uint32_t count, ShaderStageFlags shaderStageFlags), 
		(binding, type, count, shaderStageFlags))

	DEFINE_GFX_UNION(DescriptorBufferInfo, VkDescriptorBufferInfo, NA, NA,
		(Buffer buffer, uint64_t offset, uint64_t range),
		(buffer, offset, range))

	DEFINE_GFX_UNION(DescriptorImageInfo, VkDescriptorImageInfo, NA, NA,
		(ImageView imageView, Sampler sampler, ImageLayout imageLayout),
		(imageView, sampler, imageLayout))

	DEFINE_GFX_UNION(DescriptorWriteData, VkWriteDescriptorSet, NA, NA,
		(DescriptorSet dstSet, uint32_t binding, uint32_t index, DescriptorType type, const DescriptorImageInfo* imageInfo, const DescriptorBufferInfo* bufferInfo, uint32_t count),
		(dstSet, binding, index, type, imageInfo, bufferInfo, count))

	DEFINE_GFX_UNION(AttachmentDescription, VkAttachmentDescription, NA, NA,
		(Format format, SampleCountFlags sampleCount, LoadOp lop, StoreOp sop, LoadOp stencilLop, StoreOp stencilSop, ImageLayout initialLayout, ImageLayout finalLayout),
		(format, sampleCount, lop, sop, stencilLop, stencilSop, initialLayout, finalLayout))

	DEFINE_GFX_UNION(AttachmentReference, VkAttachmentReference, NA, NA,
		(uint32_t attachment, ImageLayout layout),
		(attachment, layout))

	DEFINE_GFX_UNION(SubpassDescription, VkSubpassDescription, NA, NA,
		(PipelineBindPoint bindPoint, const AttachmentReference* inputs, uint32_t inputCount, const AttachmentReference* colors, const AttachmentReference* resolves, uint32_t colorCount, const AttachmentReference* depthStencil, const uint32_t* reserves, uint32_t reserveCount),
		(bindPoint, inputs, inputCount, colors, resolves, colorCount, depthStencil, reserves, reserveCount))

	DEFINE_GFX_UNION(SubpassDependency, VkSubpassDependency, NA, NA,
		(uint32_t srcSubpass, uint32_t dstSubpass, PipelineStageFlags srcStages, PipelineStageFlags dstStages, AccessFlags srcAccess, AccessFlags dstAccess, DependencyFlags flags),
		(srcSubpass, dstSubpass, srcStages, dstStages, srcAccess, dstAccess, flags))

	DEFINE_GFX_UNION(BufferCreateInfo, struct{VkBufferCreateInfo BufferInfo;VmaAllocationCreateInfo AllocInfo;}, NA, NA, 
		(uint64_t size, BufferUsageFlags bufferUsage, MemoryUsage memoryUsage),
		(size, bufferUsage, memoryUsage))

	DEFINE_GFX_UNION(ImageCreateInfo, struct { VkImageCreateInfo ImageInfo; VmaAllocationCreateInfo AllocInfo; }, NA, NA,
		(ImageType type, Format format, Extent3D extent, uint32_t mipLevels, uint32_t arrayLayers, SampleCountFlags sampleCount, ImageTiling tiling, ImageLayout initialLayout, ImageUsageFlags imageUsage),
		(type, format, extent, mipLevels, arrayLayers, sampleCount, tiling, initialLayout, imageUsage))

	DEFINE_GFX_UNION(ImageViewCreateInfo, VkImageViewCreateInfo, NA, NA,
		(Image image, ImageViewType type, Format format, const ImageSubresourceRange& subresource),
		(image, type, format, subresource))

	DEFINE_GFX_UNION(CmdPoolCreateInfo, VkCommandPoolCreateInfo, NA, NA,
		(Queue queue),
		(queue))

	DEFINE_GFX_UNION(CmdListsCreateInfo, VkCommandBufferAllocateInfo, NA, NA,
		(CmdPool pool, CmdListLevel level, uint32_t count),
		(pool, level, count))

	DEFINE_GFX_UNION(ShaderStageInfo, VkPipelineShaderStageCreateInfo, NA, NA, 
		(Shader shader, ShaderStageFlags stage, const char* name),
		(shader, stage, name))

	DEFINE_GFX_UNION(VertexBinding, VkVertexInputBindingDescription, NA, NA,
		(uint32_t binding, uint32_t stride, InputRate inputRate),
		(binding, stride, inputRate))

	DEFINE_GFX_UNION(VertexAttribute, VkVertexInputAttributeDescription, NA, NA,
		(uint32_t binding, uint32_t location, uint32_t offset, Format format),
		(binding, location, offset, format))

	DEFINE_GFX_UNION(VertexInputInfo, VkPipelineVertexInputStateCreateInfo, NA, NA, 
		(const VertexBinding* bindings, uint32_t bindingCount, const VertexAttribute* attributes, uint32_t attributeCount),
		(bindings, bindingCount, attributes, attributeCount))

	DEFINE_GFX_UNION(InputAssemblyInfo, VkPipelineInputAssemblyStateCreateInfo, NA, NA,
		(PrimitiveTopology topology, bool primitiveRestart),
		(topology, primitiveRestart))

	DEFINE_GFX_UNION(TessellationInfo, VkPipelineTessellationStateCreateInfo, NA, NA,
		(uint32_t patchControlPoints),
		(patchControlPoints))

	DEFINE_GFX_UNION(ViewportInfo, VkPipelineViewportStateCreateInfo, NA, NA,
		(const Viewport* viewports, uint32_t viewportCount, const Scissor* scissors, uint32_t scissorCount),
		(viewports, viewportCount, scissors, scissorCount))                                

	DEFINE_GFX_UNION(RasterizationInfo, VkPipelineRasterizationStateCreateInfo, NA, NA,
		(PolygonMode polyMode, CullModeFlags cullMode, FrontFace frontFace, bool depthClamp, bool rasterizationDiscard, bool depthBias, float depthBiasConstant, float depthBiasClamp, float depthBiasSlope, float lineWidth),
		(polyMode, cullMode, frontFace, depthClamp, rasterizationDiscard, depthBias, depthBiasConstant, depthBiasClamp, depthBiasSlope, lineWidth))

	DEFINE_GFX_UNION(MultisamplingInfo, VkPipelineMultisampleStateCreateInfo, NA, NA,
		(SampleCountFlags sampleCount, bool alphaToCoverage, bool alphaToOne, bool sampleShading, float minSampleShading),
		(sampleCount, alphaToCoverage, alphaToOne, sampleShading, minSampleShading))

	DEFINE_GFX_UNION(StencilOpState, VkStencilOpState, NA, NA,
		(StencilOp fail, StencilOp pass, StencilOp depthFail, CompareOp compare, uint32_t compareMask, uint32_t writeMask, uint32_t reference),
		(fail, pass, depthFail, compare, compareMask, writeMask, reference))

	DEFINE_GFX_UNION(DepthStencilInfo, VkPipelineDepthStencilStateCreateInfo, NA, NA,
		(bool depthTest, bool depthWrite, bool depthBoundsTest, bool stencilTest, CompareOp op, StencilOpState front, StencilOpState back, float minBounds, float maxBounds),
		(depthTest, depthWrite, depthBoundsTest, stencilTest, op, front, back, minBounds, maxBounds))

	DEFINE_GFX_UNION(ColorBlendAttachmentState, VkPipelineColorBlendAttachmentState, NA, NA,
		(bool blend, BlendOp blendOp, BlendOp alphaBlendOp, ColorFlags writeMask, BlendFactor srcBlend, BlendFactor dstBlend, BlendFactor srcAlphaBlend, BlendFactor dstAlphaBlend),
		(blend, blendOp, alphaBlendOp, writeMask, srcBlend, dstBlend, srcAlphaBlend, dstAlphaBlend))

	DEFINE_GFX_UNION(ColorBlendInfo, VkPipelineColorBlendStateCreateInfo, NA, NA,
		(bool logicOp, LogicOp op, const ColorBlendAttachmentState* attachments, uint32_t attachmentCount, float blendConstants[4]),
		(logicOp, op, attachments, attachmentCount, blendConstants))

	DEFINE_GFX_UNION(DynamicInfo, VkPipelineDynamicStateCreateInfo, NA, NA,
		(const DynamicState* states, uint32_t count),
		(states, count))

	DEFINE_GFX_UNION(GraphicsPipelineCreateInfo, VkGraphicsPipelineCreateInfo, NA, NA,
		(PipelineLayout layout, RenderPass renderPass, uint32_t subpass, 
		const ShaderStageInfo* stageInfo, uint32_t stageCount, 
		const VertexInputInfo& vertexInfo, 
		const InputAssemblyInfo& inputAssemblyInfo, 
		const TessellationInfo& tessellationInfo,
		const ViewportInfo& viewportInfo,
		const RasterizationInfo& rasterizationInfo,
		const MultisamplingInfo& multisamplingInfo,
		const DepthStencilInfo& depthStencilInfo,
		const ColorBlendInfo& colorBlendInfo,
		const DynamicInfo& dynamicInfo),
		(layout, renderPass, subpass, stageInfo, stageCount, vertexInfo, inputAssemblyInfo, tessellationInfo, viewportInfo, rasterizationInfo, multisamplingInfo, depthStencilInfo, colorBlendInfo, dynamicInfo))

	DEFINE_GFX_UNION(PushConstant, VkPushConstantRange, NA, NA,
		(ShaderStageFlags stages, uint32_t offset, uint32_t size),
		(stages, offset, size))

	DEFINE_GFX_UNION(PipelineLayoutCreateInfo, VkPipelineLayoutCreateInfo, NA, NA,
		(const DescriptorLayout* layouts, uint32_t layoutCount, const PushConstant* pushConstants, uint32_t pushConstantCount),
		(layouts, layoutCount, pushConstants, pushConstantCount))

	DEFINE_GFX_UNION(RenderPassCreateInfo, VkRenderPassCreateInfo, NA, NA,
		(const AttachmentDescription* attachments, uint32_t attachmentCount, const SubpassDescription* subpasses, uint32_t subpassCount, const SubpassDependency* dependencies, uint32_t dependencyCount),
		(attachments, attachmentCount, subpasses, subpassCount, dependencies, dependencyCount))

	DEFINE_GFX_UNION(FramebufferCreateInfo, VkFramebufferCreateInfo, NA, NA,
		(RenderPass renderPass, const ImageView* attachments, uint32_t attachmentCount, uint32_t width, uint32_t height, uint32_t layers),
		(renderPass, attachments, attachmentCount, width, height, layers))

	DEFINE_GFX_UNION(DescriptorSetsCreateInfo, VkDescriptorSetAllocateInfo, NA, NA,
		(DescriptorPool pool, const DescriptorLayout* layouts, uint32_t count),
		(pool, layouts, count))

	DEFINE_GFX_UNION(DescriptorLayoutCreateInfo, VkDescriptorSetLayoutCreateInfo, NA, NA,
		(const DescriptorLayoutBinding* bindings, uint32_t count),
		(bindings, count))

	DEFINE_GFX_UNION(DescriptorPoolCreateInfo, VkDescriptorPoolCreateInfo, NA, NA,
		(const DescriptorPoolSize* poolSizes, uint32_t count, uint32_t maxSets),
		(poolSizes, count, maxSets))
	
	DEFINE_GFX_UNION(SubmitTimelineInfo, VkTimelineSemaphoreSubmitInfo, NA, NA,
		(const uint64_t* waitValues, uint32_t waitCount, const uint64_t* signalValues, uint32_t signalCount),
		(waitValues, waitCount, signalValues, signalCount))

	DEFINE_GFX_UNION(SubmitInfo, VkSubmitInfo, NA, NA,
		(const CmdList* cmdLists, const PipelineStageFlags* waitStages, uint32_t cmdListCount, const Semaphore* waitSemaphores, uint32_t waitCount, const Semaphore* signalSemaphores, uint32_t signalCount, const SubmitTimelineInfo* timelineInfo),
		(cmdLists, waitStages, cmdListCount, waitSemaphores, waitCount, signalSemaphores, signalCount, timelineInfo))

	DEFINE_GFX_UNION(InheritanceInfo, VkCommandBufferInheritanceInfo, NA, NA,
		(RenderPass renderPass, uint32_t subpass, Framebuffer framebuffer),
		(renderPass, subpass, framebuffer))

	DEFINE_GFX_UNION(BeginRecordingInfo, VkCommandBufferBeginInfo, NA, NA,
		(CmdListUsageFlags usage, const InheritanceInfo* inheritance),
		(usage, inheritance))

	DEFINE_GFX_UNION(SamplerCreateInfo, VkSamplerCreateInfo, NA, NA,
		(Filter magFilter, Filter minFilter, MipmapMode mipMode, AddressMode U, AddressMode V, AddressMode W, bool anisotropy, float maxAnisotropy, float mipBias, float minLod, float maxLod, bool compare, CompareOp op),
		(magFilter, minFilter, mipMode, U, V, W, anisotropy, maxAnisotropy, mipBias, minLod, maxLod, compare, op))

	DEFINE_GFX_UNION(SemaphoreTimelineInfo, VkSemaphoreTypeCreateInfo, NA, NA,
		(uint64_t initialValue, SemaphoreType type),
		(initialValue, type))

	DEFINE_GFX_UNION(RenderPassBeginInfo, VkRenderPassBeginInfo, NA, NA,
		(RenderPass renderPass, Framebuffer framebuffer, Scissor scissor, const ClearValue* clearValues, uint32_t clearValueCount),
		(renderPass, framebuffer, scissor, clearValues, clearValueCount))

	DEFINE_GFX_UNION(PresentInfo, VkPresentInfoKHR, NA, NA,
		(const Swapchain* swapchains, const uint32_t* imageIndices, uint32_t swapchainCount, const Semaphore* waitSemaphores, uint32_t waitCount),
		(swapchains, imageIndices, swapchainCount, waitSemaphores, waitCount))

	DEFINE_GFX_UNION(MemoryBarrier, VkMemoryBarrier, NA, NA,
		(AccessFlags srcAccess, AccessFlags dstAccess),
		(srcAccess, dstAccess))

	DEFINE_GFX_UNION(BufferBarrier, VkBufferMemoryBarrier, NA, NA,
		(AccessFlags srcAccess, AccessFlags dstAccess, uint32_t srcFamilyIndex, uint32_t dstFamilyIndex, Buffer buffer, uint64_t offset, uint64_t size),
		(srcAccess, dstAccess, srcFamilyIndex, dstFamilyIndex, buffer, offset, size))

	DEFINE_GFX_UNION(ImageBarrier, VkImageMemoryBarrier, NA, NA,
		(AccessFlags srcAccess, AccessFlags dstAccess, uint32_t srcFamilyIndex, uint32_t dstFamilyIndex, Image image, ImageLayout oldLayout, ImageLayout newLayout, const ImageSubresourceRange& subresource),
		(srcAccess, dstAccess, srcFamilyIndex, dstFamilyIndex, image, oldLayout, newLayout, subresource))




	DEFINE_GFX_FUNCTION(Initialize, 
		(API api), 
		(api), 
		UsedAPI = api;)

	DEFINE_GFX_FUNCTION(Terminate,
		(),
		(),)

	DEFINE_GFX_FUNCTION(GetRenderQueue,
		(Queue& queue),
		(queue),)

	DEFINE_GFX_FUNCTION(GetTransferQueue,
		(Queue& queue),
		(queue),)

	DEFINE_GFX_FUNCTION(CreateBuffer,
		(Buffer& handle, const BufferCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyBuffer,
		(Buffer handle),
		(handle),)

	DEFINE_GFX_FUNCTION(UploadMemory,
		(Buffer dstBuffer, MemoryCopyData* copyData, uint32_t count),
		(dstBuffer, copyData, count),)

	DEFINE_GFX_FUNCTION(CreateImage,
		(Image& handle, const ImageCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyImage,
		(Image handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateImageView,
		(ImageView& handle, const ImageViewCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyImageView,
		(ImageView handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateCmdPool,
		(CmdPool& handle, const CmdPoolCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyCmdPool,
		(CmdPool handle),
		(handle),)

	DEFINE_GFX_FUNCTION(ResetCmdPool,
		(CmdPool handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateCmdLists,
		(CmdList* cmdLists, const CmdListsCreateInfo& createInfo),
		(cmdLists, createInfo),)

	DEFINE_GFX_FUNCTION(BeginRecording,
		(CmdList cmdList, const BeginRecordingInfo& beginInfo),
		(cmdList, beginInfo),)

	DEFINE_GFX_FUNCTION(StopRecording,
		(CmdList cmdList),
		(cmdList),)

	DEFINE_GFX_FUNCTION(SubmitCmdLists,
		(Queue queue, const SubmitInfo* submitInfos, uint32_t count),
		(queue, submitInfos, count),)

	DEFINE_GFX_FUNCTION(ResetCmdList,
		(CmdList cmdList, bool releaseResources),
		(cmdList, releaseResources),)

	DEFINE_GFX_FUNCTION(CreateDescriptorPool,
		(DescriptorPool& handle, const DescriptorPoolCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyDescriptorPool,
		(DescriptorPool handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateDescriptorLayout,
		(DescriptorLayout& handle, const DescriptorLayoutCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyDescriptorLayout,
		(DescriptorLayout handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateDescriptorSets,
		(DescriptorSet* handles, const DescriptorSetsCreateInfo& createInfo),
		(handles, createInfo),)

	DEFINE_GFX_FUNCTION(WriteDescriptorSet,
		(DescriptorWriteData* writes, uint32_t count),
		(writes, count),)

	DEFINE_GFX_FUNCTION(CreateFramebuffer,
		(Framebuffer& handle, const FramebufferCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyFramebuffer,
		(Framebuffer handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateRenderPass,
		(RenderPass& handle, const RenderPassCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyRenderPass,
		(RenderPass handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateShaderCompiler,
		(ShaderCompiler& handle),
		(handle),)

	DEFINE_GFX_FUNCTION(DestroyShaderCompiler,
		(ShaderCompiler handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateShader,
		(Shader& handle, ShaderCompiler compiler, ShaderStageFlags stage, const char* code, uint32_t size),
		(handle, compiler, stage, code, size),)

	DEFINE_GFX_FUNCTION(DestroyShader,
		(Shader handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateSampler,
		(Sampler& handle, const SamplerCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroySampler,
		(Sampler handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreateSemaphore,
		(Semaphore& handle, const SemaphoreTimelineInfo* createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroySemaphore,
		(Semaphore handle),
		(handle),)

	DEFINE_GFX_FUNCTION(WaitSemaphores,
		(const Semaphore* semaphores, const uint64_t* values, uint32_t count),
		(semaphores, values, count),)
		
	DEFINE_GFX_FUNCTION(CreateSurface,
		(Surface& surface, const void* window, const void* module, Queue* presentQueue),
		(surface, window, module, presentQueue),)

	DEFINE_GFX_FUNCTION(DestroySurface,
		(Surface surface),
		(surface),)

	DEFINE_GFX_FUNCTION(CreateSwapchain,
		(Swapchain& handle, const Swapchain* old, Surface surface, Queue presentQueue, uint32_t* layers, uint32_t* imageCount, uint32_t* width, uint32_t* height),
		(handle, old, surface, presentQueue, layers, imageCount, width, height),)

	DEFINE_GFX_FUNCTION(DestroySwapchain,
		(Swapchain handle),
		(handle),)

	DEFINE_GFX_FUNCTION(GetSwapchainImages,
		(Image* images, uint32_t count, Swapchain swapchain),
		(images, count, swapchain),)

	DEFINE_GFX_FUNCTION(GetNextImage,
		(Swapchain swapchain, Semaphore signalSemaphore, uint32_t* imageIndex),
		(swapchain, signalSemaphore, imageIndex),)

	DEFINE_GFX_FUNCTION(PresentImage,
		(Queue presentQueue, const PresentInfo& presentInfo),
		(presentQueue, presentInfo),)

	DEFINE_GFX_FUNCTION(CreateGraphicsPipelines,
		(Pipeline* handles, const GraphicsPipelineCreateInfo* createInfos, uint32_t count),
		(handles, createInfos, count),)

	DEFINE_GFX_FUNCTION(DestroyPipeline,
		(Pipeline handle),
		(handle),)

	DEFINE_GFX_FUNCTION(CreatePipelineLayout,
		(PipelineLayout& handle, const PipelineLayoutCreateInfo& createInfo),
		(handle, createInfo),)

	DEFINE_GFX_FUNCTION(DestroyPipelineLayout,
		(PipelineLayout handle),
		(handle),)



	DEFINE_GFX_FUNCTION(CopyBuffer,
		(CmdList cmdList, Buffer srcBuffer, Buffer dstBuffer, const BufferCopyData* copyData, uint32_t count),
		(cmdList, srcBuffer, dstBuffer, copyData, count),)

	DEFINE_GFX_FUNCTION(CopyBufferToImage,
		(CmdList cmdList, Buffer srcBuffer, Image dstImage, ImageLayout currentLayout, const BufferImageCopyData* copyData, uint32_t count),
		(cmdList, srcBuffer, dstImage, currentLayout, copyData, count),)

	DEFINE_GFX_FUNCTION(ExecuteCmdLists,
		(CmdList cmdList, const CmdList* cmdLists, uint32_t count),
		(cmdList, cmdLists, count),)

	DEFINE_GFX_FUNCTION(BeginRenderPass,
		(CmdList cmdList, const RenderPassBeginInfo& beginInfo, bool inlineCmds),
		(cmdList, beginInfo, inlineCmds),)

	DEFINE_GFX_FUNCTION(EndRenderPass,
		(CmdList cmdList),
		(cmdList),)

	DEFINE_GFX_FUNCTION(InsertBarrier,
		(CmdList cmdList, PipelineStageFlags srcStages, PipelineStageFlags dstStages, DependencyFlags dependencies, const MemoryBarrier* memBarriers, uint32_t memBarrierCount, const BufferBarrier* bufBarriers, uint32_t bufBarrierCount, const ImageBarrier* imgBarriers, uint32_t imgBarrierCount),
		(cmdList, srcStages, dstStages, dependencies, memBarriers, memBarrierCount, bufBarriers, bufBarrierCount, imgBarriers, imgBarrierCount),)

	DEFINE_GFX_FUNCTION(BindViewports,
		(CmdList cmdList, const Viewport* viewports, uint32_t viewportCount, uint32_t startIndex),
		(cmdList, viewports, viewportCount, startIndex),)

	DEFINE_GFX_FUNCTION(BindScissors,
		(CmdList cmdList, const Scissor* scissors, uint32_t scissorCount, uint32_t startIndex),
		(cmdList, scissors, scissorCount, startIndex),)

	DEFINE_GFX_FUNCTION(BindPipeline,
		(CmdList cmdList, Pipeline pipeline, PipelineBindPoint bindPoint),
		(cmdList, pipeline, bindPoint),)

	DEFINE_GFX_FUNCTION(BindVertexBuffer,
		(CmdList cmdList, Buffer vertexBuffer, uint32_t binding, uint32_t bindingCount, uint64_t offset),
		(cmdList, vertexBuffer, binding, bindingCount, offset),)

	DEFINE_GFX_FUNCTION(BindIndexBuffer,
		(CmdList cmdList, Buffer indexBuffer, IndexType type, uint64_t offset),
		(cmdList, indexBuffer, type, offset),)

	DEFINE_GFX_FUNCTION(BindDescriptorSets,
		(CmdList cmdList, PipelineLayout layout, const DescriptorSet* sets, uint32_t descriptorSetCount, uint32_t startIndex, PipelineBindPoint bindPoint),
		(cmdList, layout, sets, descriptorSetCount, startIndex, bindPoint),)

	DEFINE_GFX_FUNCTION(Draw,
		(CmdList cmdList, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance),
		(cmdList, vertexCount, instanceCount, firstVertex, firstInstance),)

	DEFINE_GFX_FUNCTION(DrawIndexed,
		(CmdList cmdList, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, uint32_t vertexOffset, uint32_t firstInstance),
		(cmdList, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance),)
}