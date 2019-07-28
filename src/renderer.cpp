#pragma once
#include <vulkan/vulkan.h>
#include <assert.h>

VkInstance g_instance = 0;

#ifdef _DEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif

const char* extensions[] =
{
    VK_KHR_SURFACE_EXTENSION_NAME
};

const char* validationLayers[] =
{
    "VK_LAYER_LUNARG_standard_validation"
};

#define VK_CHECK(call)                          \
   do { \
        VkResult result_ = call; \
        assert(result_ == VK_SUCCESS); \
  } while(0)                 \

bool
CheckValidationLayerSupport(){
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, 0);

    VkLayerProperties *availableLayers = new VkLayerProperties[layerCount];

    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);


    return false;
}

int
InitializeVulkan(){
    //Vulkan Init
    VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    appInfo.apiVersion = VK_VERSION_1_0;
    // appInfo.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    createInfo.pApplicationInfo = &appInfo;
    createInfo.ppEnabledLayerNames = validationLayers;
    createInfo.enabledLayerCount = sizeof(validationLayers) / sizeof(validationLayers[0]);
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]);

    VK_CHECK(vkCreateInstance(&createInfo, 0, &g_instance));

    VkPhysicalDevice physicalDevices[16];
    uint32_t physicalDeviceCount = sizeof(physicalDevices) / sizeof(physicalDevices[0]);
    VK_CHECK(vkEnumeratePhysicalDevices(g_instance, &physicalDeviceCount, physicalDevices));

    return 1;
}
