#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <memory>

namespace Kanae {

class VulkanContext {
public:
    VulkanContext() = default;
    ~VulkanContext() = default;

    void initialize(const std::string& windowTitle);
    void cleanup();
    bool shouldClose() const;
    void pollEvents();
    
    // Frame rendering methods
    bool beginFrame();
    void beginRenderPass();
    void endRenderPass();
    void endFrame();

    GLFWwindow* getWindow() const { return window; }
    VkInstance getInstance() const { return instance; }
    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }
    VkDevice getDevice() const { return device; }
    VkQueue getGraphicsQueue() const { return graphicsQueue; }
    VkQueue getPresentQueue() const { return presentQueue; }
    VkSurfaceKHR getSurface() const { return surface; }
    VkSwapchainKHR getSwapchain() const { return swapchain; }
    const std::vector<VkImage>& getSwapchainImages() const { return swapchainImages; }
    const std::vector<VkImageView>& getSwapchainImageViews() const { return swapchainImageViews; }
    VkFormat getSwapchainImageFormat() const { return swapchainImageFormat; }
    VkExtent2D getSwapchainExtent() const { return swapchainExtent; }
    
    // Additional getters for ImGui integration
    uint32_t getGraphicsQueueFamily() const { return graphicsQueueFamily; }
    VkRenderPass getRenderPass() const { return renderPass; }
    VkCommandBuffer getCurrentCommandBuffer() const { return commandBuffers[currentFrame]; }
    uint32_t getSwapchainImageCount() const { return static_cast<uint32_t>(swapchainImages.size()); }
    VkDescriptorPool getDescriptorPool() const { return descriptorPool; }

private:
    void createSwapchain();
    void createImageViews();
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void cleanupSwapchain();
    void createDescriptorPool();
    
    GLFWwindow* window = nullptr;
    VkInstance instance = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkQueue graphicsQueue = VK_NULL_HANDLE;
    VkQueue presentQueue = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    
    // Queue family
    uint32_t graphicsQueueFamily = 0;
    
    // Render pass and framebuffers
    VkRenderPass renderPass = VK_NULL_HANDLE;
    std::vector<VkFramebuffer> swapchainFramebuffers;
    
    // Command pool and buffers
    VkCommandPool commandPool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers;
    
    // Synchronization objects
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    
    // Descriptor pool
    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
    
    // Frame tracking
    size_t currentFrame = 0;
    uint32_t imageIndex = 0;
    
    static const int MAX_FRAMES_IN_FLIGHT = 2;
};

} // namespace Kanae 