//
//  CommandPool.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef CommandPool_hpp
#define CommandPool_hpp

#include "Utils.h"
#include "LogicalDevice.h"

class CommandPool {
    
    KYPtr<LogicalDevice> m_LogicalDevice;
    VkCommandPool commandPool;
public:
    
    CommandPool(KYPtr<LogicalDevice> logicalDevice);
    
    void createCommandPool();
    VkCommandPool GetCommandPool();
    
    void cleanup();
};

#endif /* CommandPool_hpp */
