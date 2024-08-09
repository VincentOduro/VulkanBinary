#include "VkRenderer.h"



void VkRenderer::run()
{
    initWindow();
    initVulkan();
    //mainLoop();
    cleanup();
}

void VkRenderer::initWindow()
{
    // Initialise GLFW and OpenGL
    glfwInit();
    // Tell GLFW not to create an OpenGL context since we don't need one
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Don't worry about resizing the window for now, just disable it
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Store a handle to our window in our class
    _window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanBinary", nullptr, nullptr);

    glfwSetWindowUserPointer(_window, this); // Allows us to set the owner instance class for this window
}

void VkRenderer::initVulkan()
{
    createInstance();
}

void VkRenderer::mainLoop()
{
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();
    }
}

void VkRenderer::cleanup()
{
    vkDestroyInstance(_instance, nullptr);

    glfwDestroyWindow(_window);

    glfwTerminate();
}

void VkRenderer::createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &_instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

