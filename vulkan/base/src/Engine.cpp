//
//  Engine.cpp
//  vulkan
//
//  Created by Linkyrie on 2021/6/25.
//

#include <stdio.h>
#include "Engine.h"


KYPtr<VulkanRHI> Engine::GetVulkanRHI() {
    return m_VulkanRHI;
}

Engine* Engine::GetInstance() {
    if (m_Engine == nullptr) {
        m_Engine = new Engine;
    }
    return m_Engine;
}

void Engine::Run() {
    Init();
    run();
}

void Engine::Init() {
    m_LoadModel = std::make_shared<LoadModel>();
    m_VulkanRHI = std::make_shared<VulkanRHI>();
    m_PhysicalDevice = std::make_shared<PhysicalDevice>(m_VulkanRHI);
    m_LogicalDevice = std::make_shared<LogicalDevice>(m_PhysicalDevice);
    m_SwapChain = std::make_shared<SwapChain>(m_LogicalDevice);
    m_CommandPool = std::make_shared<CommandPool>(m_LogicalDevice);
    m_RenderPass = std::make_shared<RenderPass>(m_LogicalDevice, m_SwapChain);
    m_Buffer = std::make_shared<Buffer>(m_LogicalDevice, m_CommandPool, m_SwapChain, m_RenderPass, m_LoadModel);
    
    m_ImageView = std::make_shared<ImageView>(m_SwapChain, m_Buffer);
    m_FrameBuffer = std::make_shared<FrameBuffer>(m_SwapChain, m_ImageView, m_RenderPass);
    m_Sampler = std::make_shared<Sampler>(m_LogicalDevice, m_ImageView);
    m_Descriptor = std::make_shared<Descriptor>(m_LogicalDevice, m_SwapChain, m_ImageView, m_Sampler);
    
    m_SyncObject = std::make_shared<SyncObject>(m_SwapChain);
    
    m_Pipeline = std::make_shared<Pipeline>(m_RenderPass, m_Descriptor, m_FrameBuffer, m_Buffer, m_CommandPool);
}

void Engine::InitVulkan() {
    m_VulkanRHI->CreateInstance();
    m_VulkanRHI->setupDebugMessenger();
    m_PhysicalDevice->createSurface();
    m_PhysicalDevice->pickPhysicalDevice();
    m_LogicalDevice->createLogicalDevice();
    m_SwapChain->createSwapChain();
    m_ImageView->createImageViews();
    m_RenderPass->createRenderPass();
    m_Descriptor->createDescriptorSetLayout();
    m_Pipeline->createGraphicsPipeline();
    m_CommandPool->createCommandPool();
    m_ImageView->createColorResources();
    m_ImageView->createDepthResources();
    m_FrameBuffer->createFramebuffers();
    m_ImageView->createTextureImage();
    m_ImageView->createTextureImageView();
    m_LoadModel->loadModel();
    m_Buffer->createVertexBuffer();
    m_Buffer->createIndexBuffer();
    m_Buffer->createUniformBuffers();
    m_Descriptor->createDescriptorPool();
    m_Descriptor->createDescriptorSets();
    m_Pipeline->createCommandBuffers();
    m_SyncObject->createSyncObjects();
}

void Engine::InitWindow() { 
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    
    m_VulkanRHI->SetWindow(window);
}

void Engine::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawFrame();
    }
    auto device = m_LogicalDevice->GetDevice();
    vkDeviceWaitIdle(device);
}

void Engine::drawFrame() {
    auto inFlightFences = m_SyncObject->GetInFlightFences();
    auto device = m_LogicalDevice->GetDevice();
    auto swapChain = m_SwapChain->GetSwapChain();
    auto imageAvailableSemaphores = m_SyncObject->GetImageAvailableSemaphores();
    auto imagesInFlight = m_SyncObject->GetImagesInFlight();
    auto commandBuffers = m_Pipeline->GetCommandBuffers();
    auto renderFinishedSemaphores = m_SyncObject->GetRenderFinishedSemaphores();
    auto graphicsQueue = m_LogicalDevice->GetGraphicsQueue();
    auto presentQueue = m_LogicalDevice->GetPresentQueue();
    
    vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreateSwapChain();
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    updateUniformBuffer(imageIndex);

    if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
    }
    imagesInFlight[imageIndex] = inFlightFences[currentFrame];

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(device, 1, &inFlightFences[currentFrame]);

    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
        framebufferResized = false;
        recreateSwapChain();
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Engine::cleanup() {
    cleanupSwapChain();
    
    m_Sampler->cleanup();
    m_ImageView->cleanup();
    m_Descriptor->cleanup();
    m_Buffer->cleanup();
    m_SyncObject->cleanup();
    m_CommandPool->cleanup();
    m_LogicalDevice->cleanup();
    m_PhysicalDevice->cleanup();
    m_VulkanRHI->cleanup();
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::run() {
    InitWindow();
    InitVulkan();
    mainLoop();
    cleanup();
}

void Engine::updateUniformBuffer(uint32_t currentImage) {
    auto swapChainExtent = m_SwapChain->GetSwapChainExtent();
    auto uniformBuffersMemory = m_Buffer->GetUniformBuffersMemory();
    auto device = m_LogicalDevice->GetDevice();
    
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    void* data;
    vkMapMemory(device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
}

void Engine::recreateSwapChain() {
    int width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }
    
    m_VulkanRHI->SetWindow(window);
    
    m_LogicalDevice->waitIdle();
    cleanupSwapChain();
    m_SwapChain->createSwapChain();
    m_ImageView->createImageViews();
    m_RenderPass->createRenderPass();
    m_Pipeline->createGraphicsPipeline();
    m_ImageView->createColorResources();
    m_ImageView->createDepthResources();
    m_FrameBuffer->createFramebuffers();
    m_Buffer->createUniformBuffers();
    m_Descriptor->createDescriptorPool();
    m_Descriptor->createDescriptorSets();
    m_Pipeline->createCommandBuffers();
    
    m_SyncObject->recreateSwapChain();
}

void Engine::cleanupSwapChain() {
    m_ImageView->cleanupSwapChain();
    m_FrameBuffer->cleanupSwapChain();
    m_Pipeline->cleanupSwapChain();
    m_RenderPass->cleanupSwapChain();
    m_Buffer->cleanupSwapChain();
    m_Descriptor->cleanupSwapChain();
}



