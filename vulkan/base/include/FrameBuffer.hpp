//
//  FrameBuffer.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/26.
//

#ifndef FrameBuffer_hpp
#define FrameBuffer_hpp

#include "Utils.h"
#include "SwapChain.hpp"
#include "ImageView.hpp"
#include "RenderPass.hpp"


class FrameBuffer {
    
private:
    std::vector<VkFramebuffer> swapChainFramebuffers;
    KYPtr<SwapChain> m_SwapChain;
    KYPtr<ImageView> m_ImageView;
    KYPtr<RenderPass> m_RenderPass;
public:
    
    FrameBuffer(KYPtr<SwapChain> swapChain, KYPtr<ImageView> imageView, KYPtr<RenderPass> renderPass);
    
    void createFramebuffers();
    std::vector<VkFramebuffer>& GetSwapChainFramebuffers();
    
    void cleanupSwapChain();
};

#endif /* FrameBuffer_hpp */
