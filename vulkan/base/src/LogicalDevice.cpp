//
//  LogicalDevice.cpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#include "LogicalDevice.h"

LogicalDevice::LogicalDevice(KYPtr<PhysicalDevice> physicalDevice) : m_PhysicalDevice(physicalDevice)
{
    
}


void LogicalDevice::createLogicalDevice() {
    QueueFamilyIndices indices = m_PhysicalDevice->findQueueFamilies(m_PhysicalDevice->GetVkPhysicalDevice());

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(GetPhysicalDevice(), &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}

SwapChainSupportDetails LogicalDevice::querySwapChainSupport() {
    return m_PhysicalDevice->querySwapChainSupport(m_PhysicalDevice->GetVkPhysicalDevice());
}

VkPhysicalDevice LogicalDevice::GetPhysicalDevice() {
    return m_PhysicalDevice->GetVkPhysicalDevice();
}

VkSurfaceKHR LogicalDevice::GetSurface() { 
    return m_PhysicalDevice->GetSurface();
}

QueueFamilyIndices LogicalDevice::findQueueFamilies() { 
    return m_PhysicalDevice->findQueueFamilies(m_PhysicalDevice->GetVkPhysicalDevice());
}

VkDevice LogicalDevice::GetDevice() { 
    return device;
}

VkSampleCountFlagBits LogicalDevice::GetMsaaSamples() {
    return m_PhysicalDevice->GetMsaaSamples();
}

uint32_t LogicalDevice::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) { 
    return m_PhysicalDevice->findMemoryType(typeFilter, properties);
}

std::shared_ptr<PhysicalDevice> LogicalDevice::GetPhysicalDevicePtr() { 
    return m_PhysicalDevice;
}

VkQueue LogicalDevice::GetGraphicsQueue() { 
    return graphicsQueue;
}

VkQueue LogicalDevice::GetPresentQueue() {
    return presentQueue;
}

void LogicalDevice::cleanup() {
    vkDestroyDevice(device, nullptr);
}

void LogicalDevice::waitIdle() {
    vkDeviceWaitIdle(device);
}
