//Globals
LPCSTR g_WndClassName = "testWindow";
HWND g_hwnd = NULL;
const int g_Width = 800;
const int g_Height = 600;
VkInstance g_instance = 0;

const char* extensions[] =
{
    VK_KHR_SURFACE_EXTENSION_NAME
};

const char* validationLayers[] =
{
    "VK_LAYER_LUNARG_standard_validation"
};

#ifdef _DEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif
