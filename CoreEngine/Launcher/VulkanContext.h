#pragma once

#include <vulkan/vulkan.h>
#include <vector>

class GLFWwindow;

class VulkanContext {
public:
    VulkanContext();
    ~VulkanContext();

    void init(GLFWwindow* window);
    void cleanup();
    void beginCommandBuffer();
    void endCommandBuffer();
    void submitCommandBuffer();
    void recreateSwapchain();

    // Getters
    VkInstance getInstance() const { return m_instance; }
    VkPhysicalDevice getPhysicalDevice() const { return m_physicalDevice; }
    VkDevice getDevice() const { return m_device; }
    uint32_t getQueueFamily() const { return m_queueFamily; }
    VkQueue getQueue() const { return m_queue; }
    VkDescriptorPool getDescriptorPool() const { return m_descriptorPool; }
    VkRenderPass getRenderPass() const { return m_renderPass; }
    VkCommandBuffer getCommandBuffer() const { return m_commandBuffers[m_currentFrame]; }
    VkFramebuffer getFramebuffer() const { return m_swapchainFramebuffers[m_currentImageIndex]; }

private:
    void createInstance();
    void createSurface();
    void selectPhysicalDevice();
    void createLogicalDevice();
    void createSwapchain();
    void cleanupSwapchain();
    void createImageViews();
    void createDescriptorPool();
    void createCommandPool();
    void createRenderPass();
    void createSwapchainFramebuffers();
    void createCommandBuffers();
    void createSyncObjects();

    static const int MAX_FRAMES_IN_FLIGHT = 2;

    GLFWwindow* m_window;
    VkInstance m_instance;
    VkSurfaceKHR m_surface;
    VkPhysicalDevice m_physicalDevice;
    VkDevice m_device;
    uint32_t m_queueFamily;
    VkQueue m_queue;
    VkSwapchainKHR m_swapchain;
    std::vector<VkImage> m_swapchainImages;
    std::vector<VkImageView> m_swapchainImageViews;
    VkFormat m_swapchainImageFormat;
    VkExtent2D m_swapchainExtent;
    VkDescriptorPool m_descriptorPool;
    VkCommandPool m_commandPool;
    VkRenderPass m_renderPass;
    std::vector<VkFramebuffer> m_swapchainFramebuffers;
    std::vector<VkCommandBuffer> m_commandBuffers;
    VkFramebuffer m_framebuffer;

    // Synchronization objects
    std::vector<VkSemaphore> m_imageAvailableSemaphores;
    std::vector<VkSemaphore> m_renderFinishedSemaphores;
    std::vector<VkFence> m_inFlightFences;
    uint32_t m_currentFrame = 0;
    uint32_t m_currentImageIndex = 0;
}; 