//
//  Sampler.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef Sampler_hpp
#define Sampler_hpp

#include "Utils.h"
#include "LogicalDevice.h"
#include "ImageView.hpp"

class Sampler {
private:
    KYPtr<LogicalDevice> m_LogicalDevice;
    KYPtr<ImageView> m_ImageView;
    VkSampler textureSampler;
    
public:
    
    Sampler(KYPtr<LogicalDevice> logicalDevice, KYPtr<ImageView> imageView);
    
    void createTextureSampler();
    VkSampler GetTextureSampler();
    void cleanup();
};

#endif /* Sampler_hpp */
