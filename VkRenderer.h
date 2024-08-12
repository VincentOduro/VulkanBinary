#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//test comment
#include<vector>
#include<string>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <vulkan/vk_enum_string_helper.h >

const std::vector<const char*> validationLayers = {
"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

class VkRenderer {

public:
    void run();


private:
    /// Set window dimensions
    static constexpr uint32_t WIDTH = 800;
    static constexpr uint32_t HEIGHT = 600;




    // Handle to the GLFW window
    GLFWwindow* _window;

    // Vulkan instance handle
    VkInstance _instance;

    VkDebugUtilsMessengerEXT _debugMessenger;

    void initWindow();
    void initVulkan();  // Initializes Vulkan
    void mainLoop();    // Main game loop
    void cleanup();     // Cleans up resources
 
    void createInstance();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    void setupDebugMessenger();
    bool checkValidationLayerSupport();

    std::vector <std::string> GetRequiredExtensions();

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


