//
//  SyncObject.cpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/27.
//

#include "SyncObject.hpp"

SyncObject::SyncObject(KYPtr<SwapChain> swapChain) : m_SwapChain(swapChain)
{
    
}

void SyncObject::createSyncObjects() {
    auto swapChainImages = m_SwapChain->GetSwapChainImages();
    auto device = m_SwapChain->GetDevice();
    
    imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

void SyncObject::cleanup() {
    auto device = m_SwapChain->GetDevice();
    
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(device, inFlightFences[i], nullptr);
    }
}

void SyncObject::recreateSwapChain() {
    auto swapChainImages = m_SwapChain->GetSwapChainImages();
    imagesInFlight.resize(swapChainImages.size(), VK_NULL_HANDLE);
}

std::vector<VkFence> & SyncObject::GetImagesInFlight() {
    return imagesInFlight;
}

std::vector<VkFence> & SyncObject::GetInFlightFences() {
    return inFlightFences;
}

std::vector<VkSemaphore>& SyncObject::GetRenderFinishedSemaphores() {
    return renderFinishedSemaphores;
}

std::vector<VkSemaphore>& SyncObject::GetImageAvailableSemaphores() {
    return imageAvailableSemaphores;
}
