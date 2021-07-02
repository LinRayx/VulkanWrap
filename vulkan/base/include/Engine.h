//
//  Engine.h
//  vulkan
//
//  Created by Linkyrie on 2021/6/25.
//

#ifndef Engine_h
#define Engine_h
#include "Utils.h"
#include "VulkanRHI.h"
#include "SyncObject.hpp"
#include "LoadModel.hpp"
#include "Sampler.hpp"
#include "Buffer.hpp"
#include "FrameBuffer.hpp"
#include "CommandPool.hpp"
#include "Pipeline.hpp"
#include "Descriptor.hpp"
#include "RenderPass.hpp"
#include "ImageView.hpp"
#include "SwapChain.hpp"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"

class Engine {
public:
    
    void Run();
    
    void Init();
    void InitVulkan();
    void InitWindow();
    void mainLoop();
    void drawFrame();
    void cleanup();
    void run();
    
    virtual void prepare();
    
    void updateUniformBuffer(uint32_t currentImage);
    
    
    ~Engine() {}
    KYPtr<VulkanRHI> GetVulkanRHI();
    KYPtr<SyncObject>       m_SyncObject;
    KYPtr<LoadModel>        m_LoadModel;
    KYPtr<Sampler>          m_Sampler;
    KYPtr<Buffer>           m_Buffer;
    KYPtr<FrameBuffer>      m_FrameBuffer;
    KYPtr<CommandPool>      m_CommandPool;
    KYPtr<Pipeline>         m_Pipeline;
    KYPtr<Descriptor>       m_Descriptor;
    KYPtr<RenderPass>       m_RenderPass;
    KYPtr<ImageView>        m_ImageView;
    KYPtr<SwapChain>        m_SwapChain;
    KYPtr<PhysicalDevice>   m_PhysicalDevice;
    KYPtr<LogicalDevice>    m_LogicalDevice;
    KYPtr<VulkanRHI>        m_VulkanRHI;
    
private:
    
    GLFWwindow* window;
    static Engine* m_Engine;
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }
    
    void recreateSwapChain();
    void cleanupSwapChain();
    
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    bool framebufferResized = false;
    size_t currentFrame = 0;
};


#endif /* Engine_h */
