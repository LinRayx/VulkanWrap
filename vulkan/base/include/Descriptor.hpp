//
//  Descriptor.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef Descriptor_hpp
#define Descriptor_hpp

#include <stdio.h>
#include "Utils.h"
#include "LogicalDevice.h"
#include "SwapChain.hpp"
#include "ImageView.hpp"
#include "Sampler.hpp"

class Descriptor {
    
private:
    
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    
    KYPtr<LogicalDevice> m_LogicalDevice;
    KYPtr<SwapChain> m_SwapChain;
    KYPtr<ImageView> m_ImageView;
    KYPtr<Sampler> m_Sampler;
    
public:
    
    Descriptor(KYPtr<LogicalDevice> logicalDevice, KYPtr<SwapChain> swapChain, KYPtr<ImageView> imageView, KYPtr<Sampler> sampler);
    
    void createDescriptorSetLayout();
    void createDescriptorPool();
    void createDescriptorSets();
    VkDescriptorSetLayout GetDescriptorSetLayout();
    const std::vector<VkDescriptorSet>& GetDescriptorSets() const;
    void cleanupSwapChain();
    void cleanup();
};

#endif /* Descriptor_hpp */
