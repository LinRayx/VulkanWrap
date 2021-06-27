//
//  ImageView.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef ImageView_hpp
#define ImageView_hpp

#include "Utils.h"
#include "SwapChain.hpp"
#include "Buffer.hpp"



class ImageView {
    
public:
    
    ImageView(KYPtr<SwapChain> swapChain, KYPtr<Buffer> buffer);
    
    void createImageViews();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
    
    void createColorResources();
    void createDepthResources();
    void createTextureImage();
    void createTextureImageView();
    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
    
    VkImageView GetColorImageView();
    VkImageView GetDepthImageView();
    uint32_t GetMipLevels();
    KYPtr<Buffer> GetBuffer();
    VkImageView GetTextureImageView();
    
    void cleanupSwapChain();
    void cleanup();
    
private:
    KYPtr<SwapChain> m_SwapChain;
    KYPtr<Buffer> m_Buffer;
    
    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;
    
    
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    
    uint32_t mipLevels;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    
    
    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    
};

#endif /* ImageView_hpp */
