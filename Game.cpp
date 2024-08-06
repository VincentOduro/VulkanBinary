#include "Game.h"
#include "VkRenderer.h"




void Game::run()
{
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Game::initWindow()
{
    // Initialise GLFW and OpenGL
    glfwInit();
    // Tell GLFW not to create an OpenGL context since we don't need one
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Don't worry about resizing the window for now, just disable it
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Store a handle to our window in our class
    _window = glfwCreateWindow(800, 600, "VkLearn", nullptr, nullptr);

    glfwSetWindowUserPointer(_window, this); // Allows us to set the owner instance class for this window
}

void Game::initVulkan()
{
   //createInstance();
}

void Game::mainLoop() {
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();
    }
}

void Game::cleanup() {
    //vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(_window);

    glfwTerminate();
}