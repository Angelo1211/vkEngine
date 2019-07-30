#pragma once
#include "common.cpp"
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

VkPhysicalDevice pickPhysicalDevice(VkPhysicalDevice * physicalDevices, uint32_t physicalDeviceCount){
    for(uint32_t i = 0; i < physicalDeviceCount; ++i){
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(physicalDevices[i], &properties);

        if(properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
            printf("Picking discrete GPU %s!\n", properties.deviceName);
            return physicalDevices[i];
        }
    }

    if(physicalDeviceCount > 0){
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(physicalDevices[0], &properties);

        printf("Picking fallback GPU %s!\n", properties.deviceName);
        return physicalDevices[0];
    }
    printf("No physical devices!\n");
    return 0;
}

int
InitializeVulkan(){
    //Vulkan Init
    VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    appInfo.apiVersion = VK_API_VERSION_1_1;

    VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    createInfo.pApplicationInfo = &appInfo;
    createInfo.ppEnabledLayerNames = validationLayers;
    createInfo.enabledLayerCount = NELEM(validationLayers);
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.enabledExtensionCount = NELEM(extensions);

    VK_CHECK(vkCreateInstance(&createInfo, 0, &g_instance));

    VkPhysicalDevice physicalDevices[16];
    uint32_t physicalDeviceCount = NELEM(physicalDevices);
    VK_CHECK(vkEnumeratePhysicalDevices(g_instance, &physicalDeviceCount, physicalDevices));

    VkPhysicalDevice physicalDevice = pickPhysicalDevice(physicalDevices, physicalDeviceCount);
    assert(physicalDevice && "Install VK properly fool!\n");
    return 1;
}
