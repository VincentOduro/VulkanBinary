#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//test comment
#include <iostream>
#include <stdexcept>
#include <cstdlib>

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

    void initWindow();
    void initVulkan();  // Initializes Vulkan
    void mainLoop();    // Main game loop
    void cleanup();     // Cleans up resources
 
    void createInstance();

 };


