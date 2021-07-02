//
//  FrameBuffer.cpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#include "FrameBuffer.hpp"

FrameBuffer::FrameBuffer(KYPtr<SwapChain> swapChain, KYPtr<ImageView> imageView, KYPtr<RenderPass> renderPass) : m_SwapChain(swapChain), m_ImageView(imageView), m_RenderPass(renderPass)
{
    
}

void FrameBuffer::createFramebuffers() {
    auto swapChainImageViews = m_SwapChain->GetSwapChainImageViews();
    auto swapChainExtent = m_SwapChain->GetSwapChainExtent();
    auto renderPass = m_RenderPass->GetRenderPass();
    auto device = m_RenderPass->GetLogicalDevice()->GetDevice();
    
    swapChainFramebuffers.resize(swapChainImageViews.size());
    
    for (size_t i = 0; i < swapChainImageViews.size(); i++) {
        std::array<VkImageView, 3> attachments = {
            m_ImageView->GetColorImageView(),
            m_ImageView->GetDepthImageView(),
            swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

std::vector<VkFramebuffer>& FrameBuffer::GetSwapChainFramebuffers() {
    return swapChainFramebuffers;
}

void FrameBuffer::cleanupSwapChain() {
    auto device = m_SwapChain->GetDevice();
    
    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }
}
