#pragma once
#include "VkRenderer.h"
//#include "InputHandler.h"
//#include "AssetManager.h"



class Game {
public:
    Game() = default;   // Constructor to initialize the game
    ~Game() = default;  // Destructor to clean up resources

    void run(); // Runs the main game loop

private:


    GLFWwindow* _window;          // Pointer to the GLFW window
    VkRenderer vulkanRenderer; // Vulkan renderer instance
    //InputHandler inputHandler;   // Input handler instance
    //AssetManager assetManager;   // Asset manager instance
};
