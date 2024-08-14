#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <string>
#include <cstdlib>
#include <optional>

#include <vulkan/vk_enum_string_helper.h >



struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};


class VkRenderer {

public:
    void run();


private:
    /// Set window dimensions
    static constexpr uint32_t WIDTH = 800;
    static constexpr uint32_t HEIGHT = 600;

    const std::vector<const char*> _validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

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

    void InitWindow();
    void InitVulkan();  // Initializes Vulkan
    void MainLoop();    // Main game loop
    void Cleanup();     // Cleans up resources
 
    void CreateInstance();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    void SetupDebugMessenger();
    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);


    bool CheckValidationLayerSupport();

    std::vector<std::string> GetRequiredExtensions();


    static void VK_CHECK_RESULT(VkResult result, std::string action)
    {
#ifdef _DEBUG 
        if (result != VK_SUCCESS) {
            // Using string_VkResult to convert the result code into its string equivalent
            throw std::runtime_error("failed to " + action + "!. Error: " + string_VkResult(result));
        }
#endif
    }

    void PrintDebugInfo();
 };

