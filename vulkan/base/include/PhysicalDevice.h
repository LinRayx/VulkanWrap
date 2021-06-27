//
//  PhysicalDevice.h
//  vulkan
//
//  Created by Linkyrie on 2021/6/25.
//

#ifndef PhysicalDevice_h
#define PhysicalDevice_h

#include "Utils.h"
#include "VulkanRHI.h"

class PhysicalDevice {
public:
    PhysicalDevice(KYPtr<VulkanRHI> vukanRHI);
    void pickPhysicalDevice();
    void createSurface();
    VkPhysicalDevice GetVkPhysicalDevice();
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    VkSurfaceKHR GetSurface();
    VkSampleCountFlagBits GetMsaaSamples();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkFormat findDepthFormat();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    
    void cleanup();
    
private:
    bool isDeviceSuitable(VkPhysicalDevice device);
    std::vector<const char*> getRequiredExtensions();
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    VkSampleCountFlagBits getMaxUsableSampleCount();
    
private:
    VkSurfaceKHR surface;
    
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    
    bool enableValidationLayers;
    
    KYPtr<VulkanRHI> m_VulkanRHI;
};

#endif /* PhysicalDevice_h */
