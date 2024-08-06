#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//test comment
#include <iostream>
#include <stdexcept>
#include <cstdlib>

class VkRenderer {

private:
    /// Set window dimensions
    static constexpr uint32_t WIDTH = 800;
    static constexpr uint32_t HEIGHT = 600;

    // Handle to the GLFW window
    GLFWwindow* window;

    // Vulkan instance handle
    VkInstance instance;

    void initWindow();
    void createInstance();
 

 };


