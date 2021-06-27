//
//  VulkanRHI.h
//  vulkan
//
//  Created by Linkyrie on 2021/6/25.
//

#ifndef VulkanRHI_h
#define VulkanRHI_h

#include "Utils.h"

class VulkanRHI {
    
public:
    void CreateInstance();
    void setupDebugMessenger();
    
    VkInstance GetInstance();
    
    void SetWindow(GLFWwindow* win);
    GLFWwindow* GetWindow();
    
    void cleanup();
    
private:
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    
    VkInstance instance;
    
    VkDebugUtilsMessengerEXT debugMessenger;
    
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }
    
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    
    GLFWwindow* window;
};

#endif /* VulkanRHI_h */
