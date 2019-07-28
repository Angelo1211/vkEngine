@echo off
set arg1=%1
set VK_INSTANCE_LAYERS=VK_LAYER_LUNARG_standard_validation
set VK_LAYER_PATH=%VULKAN_SDK%\\Bin
call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64
devenv /NoSplash build\%arg1%.exe
