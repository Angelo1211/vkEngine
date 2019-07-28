@echo off
set arg1=%1
set includePaths=/I %VULKAN_SDK%\\Include
set libraries=user32.lib gdi32.lib %VULKAN_SDK%\\Lib\\vulkan-1.lib
set compilerflags=/Od /MTd /Zi /EHsc /FC %includePaths%
call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64
set linkerflags= %libraries% /subsystem:console /OUT:%arg1%.exe
mkdir build
pushd build
cl %compilerflags% ..\src\main.cpp /link %linkerflags%
popd
