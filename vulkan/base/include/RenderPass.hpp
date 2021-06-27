//
//  RenderPass.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef RenderPass_hpp
#define RenderPass_hpp

#include <stdio.h>
#include "Utils.h"
#include "LogicalDevice.h"
#include "SwapChain.hpp"

class RenderPass {
    
private:
    VkRenderPass renderPass;
    
    KYPtr<LogicalDevice> m_LogicalDevice;
    KYPtr<SwapChain> m_SwapChain;
public:
    
    RenderPass(KYPtr<LogicalDevice> logicalDevice, KYPtr<SwapChain> swapChain);
    
    void createRenderPass();
    KYPtr<LogicalDevice> GetLogicalDevice();
    KYPtr<SwapChain> GetSwapChain();
    VkRenderPass GetRenderPass();
    void cleanupSwapChain();
};

#endif /* RenderPass_hpp */
