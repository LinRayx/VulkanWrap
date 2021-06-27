//
//  SwapChain.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef SwapChain_hpp
#define SwapChain_hpp

#include <stdio.h>
#include "Utils.h"
#include "LogicalDevice.h"


class SwapChain {
    
public:
    SwapChain(KYPtr<LogicalDevice> logicalDevice);
    
    void createSwapChain();
    VkFormat GetSwapChainImageFormat();
    std::vector<VkImage>& GetSwapChainImages();
    std::vector<VkImageView>& GetSwapChainImageViews();
    KYPtr<LogicalDevice> GetLogicalDevice();
    VkDevice GetDevice();
    VkExtent2D GetSwapChainExtent();
    VkSwapchainKHR GetSwapChain();
    
    void cleanupSwapChain();
    
private:
    KYPtr<LogicalDevice> m_LogicalDevice;
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    
    
    GLFWwindow* window;
};
#endif /* SwapChain_hpp */
