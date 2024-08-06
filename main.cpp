// Main.cpp
#include "VkRenderer.h" // Include the VkRenderer class definition
#include "Game.h"
#include <vulkan/vulkan.h> // Include Vulkan headers



int main()
{
    // Create an instance of VkRenderer
    Game app;

    try {
        // Attempt to run the renderer
        app.run();
    }
    catch (const std::exception& e) {
        // If an exception is caught, print the error message and return failure
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Return success if no exception occurs
    return EXIT_SUCCESS;
}
