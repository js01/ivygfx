#ifndef SWAPCHAIN_CHK_HPP
#define SWAPCHAIN_CHK_HPP

#include <vulkan/vulkan.h>
#include <vector>

#include "window.hpp"
#include "physical_device.hpp"
#include "logical_device.hpp"

namespace ivy {

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class SwapChain {

        public:

            SwapChain(ivy::PhysicalDevice physicalDevice,     
                        VkSurfaceKHR& surface,
                        ivy::LogicalDevice& logicalDevice,
                        GLFWwindow* window_ptr, ivy::QueueManager queueManager);

            ~SwapChain();

            // ***** FUNCTIONS FOR 3 SWAP CHAIN PROPERTIES:
            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

            static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window_ptr);
            // *****

            // NB the swap chain is not actually supported by default; it is highly tied to
            // the windowing system
            static SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

            SwapChainSupportDetails getSwapChainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

            // Create a swap chain given a physical device, a surface, and a window
            // TODO: is the window necessary or can we pass something simpler in?
            void createSwapChain(const PhysicalDevice& physicalDevice, 
                                const VkSurfaceKHR& surf, LogicalDevice& logicalDevice,
                                GLFWwindow* window_ptr, QueueManager& queueManager);

            void createImageViews(VkDevice& device);
            void createFrameBuffers();

            void acquireNextImage(uint32_t& imageIndex, VkSemaphore& semaphore);


            VkExtent2D& getSwapChainExtent();    
            VkFormat& getSwapChainImageFormat();    
            std::vector<VkImageView>& getSwapChainImageViews();

            VkSwapchainKHR& getSwapChainHandle() { return swapChain; }

        private:

            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            std::vector<VkImageView> swapChainImageViews;
            VkExtent2D swapChainExtent;
            LogicalDevice& logicalDeviceHandle;
            void callVkDestructors();

    };
}

#endif