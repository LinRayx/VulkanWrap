//
//  Sampler.cpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#include "Sampler.hpp"

Sampler::Sampler(KYPtr<LogicalDevice> logicalDevice, KYPtr<ImageView> imageView) : m_LogicalDevice(logicalDevice), m_ImageView(imageView)
{
    
}

void Sampler::createTextureSampler() {
    auto physicalDevice = m_LogicalDevice->GetPhysicalDevice();
    auto device = m_LogicalDevice->GetDevice();
    auto mipLevels = m_ImageView->GetMipLevels();
    
    VkPhysicalDeviceProperties properties{};
    vkGetPhysicalDeviceProperties(physicalDevice, &properties);

    VkSamplerCreateInfo samplerInfo{};
    samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    samplerInfo.anisotropyEnable = VK_TRUE;
    samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    samplerInfo.minLod = 0.0f;
    samplerInfo.maxLod = static_cast<float>(mipLevels);
    samplerInfo.mipLodBias = 0.0f;

    if (vkCreateSampler(device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
        throw std::runtime_error("failed to create texture sampler!");
    }
}

VkSampler Sampler::GetTextureSampler() { 
    return textureSampler;
}

void Sampler::cleanup() {
    auto device = m_LogicalDevice->GetDevice();
    vkDestroySampler(device, textureSampler, nullptr);
}
