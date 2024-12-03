#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>

#include "Vertex.h"


#include <vulkan/vk_enum_string_helper.h >
const std::vector<const char*> _validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> _deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


class VkRenderer {

public:
    void run();
    bool _framebufferResized = false;

private:
        
    /// Set window dimensions
    static constexpr uint32_t WIDTH = 800;
    static constexpr uint32_t HEIGHT = 600;
    
    const int MAX_FRAMES_IN_FLIGHT = 2;




#ifdef NDEBUG
    const bool _enableValidationLayers = false;
#else
    const bool _enableValidationLayers = true;
#endif


    // Handle to the GLFW window
    GLFWwindow* _window;

    // Vulkan instance handle
    VkInstance _instance;
    

    VkDebugUtilsMessengerEXT _debugMessenger;
    
    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    
    VkDevice _device;
    VkQueue _graphicsQueue;

    VkSurfaceKHR _surface;
    VkQueue _presentQueue;

    VkSwapchainKHR _swapChain;
    std::vector<VkImage> _swapChainImages;
    VkFormat _swapChainImageFormat;
    VkExtent2D _swapChainExtent;

    std::vector<VkImageView> _swapChainImageViews;

    VkPipelineLayout _pipelineLayout;
    
    VkRenderPass _renderPass;

    VkPipeline _graphicsPipeline;
 
    std::vector<VkFramebuffer> _swapChainFramebuffers;

    VkCommandPool _commandPool;
    std::vector<VkCommandBuffer> _commandBuffers;

    std::vector<VkSemaphore> _imageAvailableSemaphores;
    std::vector<VkSemaphore> _renderFinishedSemaphores;
    std::vector<VkFence>  _inFlightFences;

    uint32_t _currentFrame = 0;

    VkBuffer _vertexBuffer;
    VkDeviceMemory _vertexBufferMemory;

    


    void InitWindow();
    void InitVulkan();  // Initializes Vulkan
    void MainLoop();    // Main game loop
    void Cleanup();     // Cleans up resources
 
    void CreateInstance();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void SetupDebugMessenger();

    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    bool CheckValidationLayerSupport();

    std::vector<std::string> GetRequiredExtensions();
    void CreateLogicalDevice();

    void CreateSurface();
    void CreateSwapChain();
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    void CreateImageViews();

    void CreateGraphicsPipeline();
    VkShaderModule CreateShaderModule(const std::vector<char>& code);

    void CreateRenderPass();

    void CreateFramebuffers();

    void CreateCommandPool();

    void CreateCommandBuffers();

    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    
    void DrawFrame();

    void CreateSyncObjects();

    void RecreateSwapChain();

    void CleanupSwapChain();

    void CreateVertexBuffer();

    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    //static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    static void VK_CHECK_RESULT(VkResult result, std::string action)
    {
#ifdef _DEBUG 
        if (result != VK_SUCCESS) {
            // Using string_VkResult to convert the result code into its string equivalent
            throw std::runtime_error("failed to " + action + "!. Error: " + string_VkResult(result));
        }
#endif
    }

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
    {
        auto app = reinterpret_cast<VkRenderer*>(glfwGetWindowUserPointer(window));

        app->_framebufferResized = true;
    }

    void PrintDebugInfo();
 };

