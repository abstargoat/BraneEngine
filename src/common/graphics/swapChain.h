#pragma once

#include "window.h"

#include <algorithm>
#include <vector>
#include <array>

namespace graphics
{
	class SwapChain
	{
		Window* _window;
		VkSwapchainKHR _swapChain;

		std::vector<VkImage> _images;
		std::vector<VkImageView> _imageViews;

		std::vector<VkSemaphore> _imageAvailableSemaphores;

		VkImage _depthImage;
		VkDeviceMemory _depthImageMemory;
		VkImageView _depthImageView;

		VkFormat _imageFormat;
		VkFormat _depthImageFormat;
		VkExtent2D _extent;
		size_t _size;
		uint32_t _currentFrame;

		void createSwapChain();
		void createImageViews();
		void createDepthResources();


		VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat findDepthFormat();

	public:
		SwapChain(Window* window);
		~SwapChain();

		VkSwapchainKHR get();
		VkResult acquireNextImage();
		const uint32_t&  currentFrame();
		uint32_t  nextFrame();

		VkSemaphore currentSemaphore();

		size_t size();
		VkExtent2D extent();
		VkFormat imageFormat();
		VkFormat depthImageFormat();
		const std::vector<VkImageView>& getImages();
		VkImageView depthTexture();

		void resize();
	};
}