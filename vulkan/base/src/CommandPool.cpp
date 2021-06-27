//
//  CommandPool.cpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#include "CommandPool.hpp"

void CommandPool::createCommandPool() {
    QueueFamilyIndices queueFamilyIndices = m_LogicalDevice->findQueueFamilies();

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(m_LogicalDevice->GetDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create graphics command pool!");
    }
}

VkCommandPool CommandPool::GetCommandPool() { 
    return commandPool;
}

CommandPool::CommandPool(std::shared_ptr<LogicalDevice> logicalDevice) : m_LogicalDevice(logicalDevice)
{
    
}

void CommandPool::cleanup() {
    auto device = m_LogicalDevice->GetDevice();
    vkDestroyCommandPool(device, commandPool, nullptr);
}
