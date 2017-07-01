//
// Created by Piasy on 29/06/2017.
//

#ifndef VULKANTUTORIAL_ANDROID_VULKAN_TRIANGLE_H
#define VULKANTUTORIAL_ANDROID_VULKAN_TRIANGLE_H

#include <android/log.h>
#include <android/asset_manager.h>

#include <vector>
#include <array>
#include <string>

#include <glm.hpp>
#include <vulkan_wrapper.h>

#define APP_NAME "VK-TUTORIAL"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, APP_NAME, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, APP_NAME, __VA_ARGS__))

#define STATE_RUNNING 1
#define STATE_PAUSED 2
#define STATE_EXIT 3

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;

    bool isComplete() {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};

struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

class HelloTriangleApplication {
public:
    HelloTriangleApplication(
            AAssetManager *assetManager,
            const char *vertexShader,
            const char *fragmentShader) :
            assetManager(assetManager),
            vertexShader(std::string(vertexShader)),
            fragmentShader(std::string(fragmentShader)),
            state(STATE_RUNNING) {
    }

    void run(ANativeWindow *window);

    void pause();

    inline void resume() {
        state = STATE_RUNNING;
    }

    void surfaceChanged();

    inline void stop() {
        state = STATE_EXIT;
    }

private:
    inline void initWindow(ANativeWindow *window) {
        this->window = window;
    }

    void initVulkan();

    void mainLoop();

    void cleanUp();

    void createInstance();

    void setUpDebugCallback();

    void createSurface();

    void pickPhysicalDevice();

    void createLogicalDevice();

    void createSwapchain();

    void createImageViews();

    void createRenderPass();

    void createGraphicsPipeline();

    void createFramebuffers();

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                      VkBuffer &buffer, VkDeviceMemory &bufferMemory);

    void createCommandPool();

    void createVertexBuffer();

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createCommandBuffers();

    void createSemaphores();

    void drawFrame();

    void recreateSwapchain();

    void cleanupSwapchain();

    std::vector<char> readAsset(std::string name);

    VkShaderModule createShaderModule(const std::vector<char> &code);

    bool isDeviceSuitable(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device);

    AAssetManager *assetManager;
    std::string vertexShader;
    std::string fragmentShader;
    int state;

    VkInstance instance;
    VkDebugReportCallbackEXT callback;
    ANativeWindow *window;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> swapchainFramebuffers;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkCommandPool commandPool;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    std::vector<VkCommandBuffer> commandBuffers;

    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
};

#endif //VULKANTUTORIAL_ANDROID_VULKAN_TRIANGLE_H
