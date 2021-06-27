//
//  SyncObject.hpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/27.
//

#ifndef SyncObject_hpp
#define SyncObject_hpp

#include "Utils.h"
#include "SwapChain.hpp"

class SyncObject {
    
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    KYPtr<SwapChain> m_SwapChain;

public:
    
    SyncObject(KYPtr<SwapChain> swapChain);
    void createSyncObjects();
    void cleanup();
    void recreateSwapChain();
  
    std::vector<VkFence>& GetImagesInFlight();
    std::vector<VkFence>& GetInFlightFences();
    std::vector<VkSemaphore>& GetRenderFinishedSemaphores();
    std::vector<VkSemaphore>& GetImageAvailableSemaphores();
};

#endif /* SyncObject_hpp */
