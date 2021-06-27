//
//  LogicalDevice.h
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef LogicalDevice_h
#define LogicalDevice_h


#include "Utils.h"

#include "PhysicalDevice.h"
class LogicalDevice {
    
public:
    LogicalDevice(KYPtr<PhysicalDevice> physicalDevice);
    
    void createLogicalDevice();
    SwapChainSupportDetails querySwapChainSupport();
    QueueFamilyIndices findQueueFamilies();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkPhysicalDevice GetPhysicalDevice();
    KYPtr<PhysicalDevice> GetPhysicalDevicePtr();
    VkSurfaceKHR GetSurface();
    VkDevice GetDevice();
    VkSampleCountFlagBits GetMsaaSamples();
    VkQueue GetGraphicsQueue();
    VkQueue GetPresentQueue();
    void waitIdle();
    void cleanup();
    
private:
    KYPtr<PhysicalDevice> m_PhysicalDevice;
    
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
};
#endif /* LogicalDevice_h */
