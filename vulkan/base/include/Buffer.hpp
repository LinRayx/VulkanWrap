//
//  Buffer.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include "Utils.h"
#include "LogicalDevice.h"
#include "CommandPool.hpp"
#include "SwapChain.hpp"
#include "RenderPass.hpp"
#include "LoadModel.hpp"


class Buffer {
private:
    KYPtr<LogicalDevice> m_LogicalDevice;
    KYPtr<CommandPool> m_CommandPool;
    KYPtr<SwapChain> m_SwapChain;
    KYPtr<RenderPass> m_RenderPass;
    KYPtr<LoadModel> m_LoadModel;
    
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkBuffer vertexBuffer;
    VkBuffer indexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkDeviceMemory indexBufferMemory;
    
public:
    
    Buffer(KYPtr<LogicalDevice> logicalDevice, KYPtr<CommandPool> commandPool, KYPtr<SwapChain> swapChain, KYPtr<RenderPass> renderPass, KYPtr<LoadModel> loadModel);
    
    void createUniformBuffers();
    
    void createVertexBuffer();
    void createIndexBuffer();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    
    VkBuffer GetVertexBuffer();
    VkBuffer GetIndexBuffer();
    const std::vector<VkBuffer>& GetUniformBuffers() const;

    KYPtr<LogicalDevice> GetLogicalDevice();
    KYPtr<LoadModel> GetLoadModel();
    std::vector<VkDeviceMemory>& GetUniformBuffersMemory();
    
    void cleanupSwapChain();
    void cleanup();
};

#endif /* Buffer_hpp */
