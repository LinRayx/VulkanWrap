//
//  Pipeline.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef Pipeline_hpp
#define Pipeline_hpp

#include <stdio.h>
#include "Utils.h"
#include "RenderPass.hpp"
#include "Descriptor.hpp"
#include "FrameBuffer.hpp"
#include "Buffer.hpp"
#include "CommandPool.hpp"

class Pipeline {
    
    VkShaderModule createShaderModule(const std::vector<char>& code);
    KYPtr<RenderPass> m_RenderPass;
    KYPtr<Descriptor> m_Descriptor;
    KYPtr<FrameBuffer> m_FrameBuffer;
    KYPtr<Buffer> m_Buffer;
    KYPtr<CommandPool> m_CommandPool;
    
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkCommandBuffer> commandBuffers;
    
    static std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t) file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }
    
public:
    
    Pipeline(KYPtr<RenderPass> renderPass, KYPtr<Descriptor> descriptor, KYPtr<FrameBuffer> frameBuffer, KYPtr<Buffer> buffer, KYPtr<CommandPool> commandPool);
    
    void createGraphicsPipeline();
    VkPipelineLayout GetPipelineLayout();
    VkPipeline GetGraphicsPipeline();
    void createCommandBuffers();
    void cleanupSwapChain();
    std::vector<VkCommandBuffer>& GetCommandBuffers();
};

#endif /* Pipeline_hpp */
