export module Viewport;
import Platform;
import Graphics;
import stdlib;

export
template<uint32_t MAX_IMAGE_COUNT>
class Viewport
{
private:
	PLTF::Window* Window;
	const GFX::RenderPass& RenderPass;
	GFX::Surface Surface;
	GFX::Queue PresentQueue;
	uint32_t LayerCount;
	uint32_t ImageCount;
	uint32_t Width;
	uint32_t Height;
	bool Resized = false;

	uint32_t currentSwapchain = 0;
	struct SwapchainData {
		GFX::Swapchain Swapchain;
		GFX::Image DepthBuffer;
		GFX::ImageView ImageViews[MAX_IMAGE_COUNT + 1];
		GFX::Framebuffer framebuffers[MAX_IMAGE_COUNT];
		uint32_t presentIndex;
	} swapchainData[MAX_IMAGE_COUNT] = { 0 };

	SwapchainData& GetCurrent() { return swapchainData[currentSwapchain]; }
	const SwapchainData& GetCurrent() const { return swapchainData[currentSwapchain]; }

	void CreateSwapchain(uint32_t swapchainIndex)
	{
		GFX::CreateSwapchain(swapchainData[swapchainIndex].Swapchain, &GetCurrent().Swapchain, Surface, PresentQueue, &LayerCount, &ImageCount, &Width, &Height);

		GFX::Image images[MAX_IMAGE_COUNT];
		GFX::GetSwapchainImages(images, ImageCount, swapchainData[swapchainIndex].Swapchain);

		GFX::CreateImage(swapchainData[swapchainIndex].DepthBuffer, GFX::InitImageCreateInfo(
			GFX::IMAGE_TYPE_2D,
			GFX::FORMAT_D16_UNORM,
			{ Width, Height, 1 },
			1,
			LayerCount,
			GFX::SAMPLE_COUNT_1_BIT,
			GFX::IMAGE_TILING_OPTIMAL,
			GFX::IMAGE_LAYOUT_UNDEFINED,
			GFX::IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
		));

		GFX::CreateImageView(swapchainData[swapchainIndex].ImageViews[MAX_IMAGE_COUNT], GFX::InitImageViewCreateInfo(
			swapchainData[swapchainIndex].DepthBuffer,
			GFX::IMAGE_VIEW_TYPE_2D,
			GFX::FORMAT_D16_UNORM,
			GFX::InitImageSubresourceRange(
				GFX::IMAGE_ASPECT_DEPTH_BIT,
				0,
				1,
				0,
				LayerCount
			)
		));

		GFX::ImageSubresourceRange colorRange = GFX::InitImageSubresourceRange(
			GFX::IMAGE_ASPECT_COLOR_BIT,
			0,
			1,
			0,
			LayerCount
		);

		for (uint32_t i = 0; i < MAX_IMAGE_COUNT; i++) {
			GFX::CreateImageView(swapchainData[swapchainIndex].ImageViews[i], GFX::InitImageViewCreateInfo(
				images[i],
				GFX::IMAGE_VIEW_TYPE_2D,
				GFX::FORMAT_B8G8R8A8_UNORM,
				colorRange
			));

			GFX::ImageView attachments[2] = { swapchainData[swapchainIndex].ImageViews[i], swapchainData[swapchainIndex].ImageViews[MAX_IMAGE_COUNT] };
			GFX::CreateFramebuffer(swapchainData[swapchainIndex].framebuffers[i], GFX::InitFramebufferCreateInfo(
				RenderPass,
				attachments,
				2,
				Width,
				Height,
				LayerCount
			));
		}
	}

	void DestroySwapchain(uint32_t swapchainIndex)
	{
		for (uint32_t i = 0; i < MAX_IMAGE_COUNT + 1; i++) {
			GFX::DestroyImageView(swapchainData[swapchainIndex].ImageViews[i]);
		}
		for (uint32_t i = 0; i < MAX_IMAGE_COUNT; i++) {
			GFX::DestroyFramebuffer(swapchainData[swapchainIndex].framebuffers[i]);
		}
		GFX::DestroySwapchain(swapchainData[swapchainIndex].Swapchain);
		GFX::DestroyImage(swapchainData[swapchainIndex].DepthBuffer);

		swapchainData[swapchainIndex] = {0};
	}

public:
	Viewport(uint32_t width, uint32_t height, uint32_t imageCount, uint32_t layerCount, const GFX::RenderPass& renderPass, const EVNT::EventCallbackFn& callback)
		: RenderPass(renderPass), LayerCount(layerCount), ImageCount(imageCount), Width(width), Height(height)
	{
		Window = PLTF::CreateWindow(width, height, "Gravity: Control");
		Window->SetEventCallback(callback);

		GFX::CreateSurface(Surface, Window->GetNativeWindow(), Window->GetModule(), &PresentQueue);
		CreateSwapchain(0);
	}

	~Viewport()
	{
		for (uint32_t i = 0; i < MAX_IMAGE_COUNT; i++) {
			DestroySwapchain(i);
		}

		GFX::DestroySurface(Surface);

		delete Window;
	}

	void GetNextImage(GFX::Semaphore signalSemaphore)
	{
		Window->OnUpdate();

		if (Resized) {
			uint32_t nextIndex = (currentSwapchain + 1) % MAX_IMAGE_COUNT;

			DestroySwapchain(nextIndex);
			CreateSwapchain(nextIndex);

			currentSwapchain = nextIndex;
			Resized = false;
		}

		GFX::GetNextImage(GetCurrent().Swapchain, signalSemaphore, &GetCurrent().presentIndex);
	}

	void PresentImage(const GFX::Semaphore* waitSemaphores, uint32_t count)
	{
		GFX::PresentImage(PresentQueue, GFX::InitPresentInfo(
			&GetCurrent().Swapchain,
			&GetCurrent().presentIndex,
			1,
			waitSemaphores,
			count
		));
	}

	void Resize(uint32_t width, uint32_t height)
	{
		Resized = true;
		Width = width;
		Height = height;
	}

	const GFX::Framebuffer& GetFramebuffer() const { return GetCurrent().framebuffers[GetCurrent().presentIndex]; }
	uint32_t GetWidth() { return Width; }
	uint32_t GetHeight() { return Height; }
};