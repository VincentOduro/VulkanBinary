#include "VkRenderer.h"

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT _debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, _debugMessenger, pAllocator);
    }
}


void VkRenderer::run()
{
    initWindow();
    initVulkan();
#ifdef _DEBUG
    PrintDebugInfo();
#endif
    mainLoop();
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
    // Optional info for the driver
    VkApplicationInfo appInfo{}; // Curly braces very important here, they initialize all fields to 0/null/a defined value
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanBinary";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0; // TODO: Update version

    // Mandatory info to create the instance
    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &appInfo;

    std::vector<std::string> requiredExtensions = GetRequiredExtensions();

    std::vector<const char*> extensionsCString;
    extensionsCString.reserve(requiredExtensions.size());

    for (const auto& extension : requiredExtensions)
    {
        extensionsCString.push_back(extension.c_str());
    }


    instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    instanceCreateInfo.ppEnabledExtensionNames = extensionsCString.data();
    instanceCreateInfo.enabledLayerCount = 0; // TODO: Enable validation layers

    VK_CHECK_RESULT(vkCreateInstance(&instanceCreateInfo, nullptr, &_instance), "create instance");
}

void VkRenderer::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

void VkRenderer::setupDebugMessenger()
{
    if (!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(_instance, &createInfo, nullptr, &_debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

bool VkRenderer::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

std::vector<std::string> VkRenderer::GetRequiredExtensions()
{
    std::vector<std::string> requiredExtensions;

    /// GLFW EXTENSIONS
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);


    for (size_t i = 0; i < glfwExtensionCount; i++)
    {
        const std::string extension(glfwExtensions[i]);
        requiredExtensions.push_back(extension);
    }

    return requiredExtensions;
}

void VkRenderer::PrintDebugInfo()
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "Available extensions: " << "\n";
    for (const auto& extension : extensions)
    {
        std::cout << extension.extensionName << ", Version: " << extension.specVersion << "\n";
    }
}


