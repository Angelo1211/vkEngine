@echo off
set arg1=%1
set includePaths=/I %VULKAN_SDK%\\Include
set compilerflags=/Od /Zi /EHsc /FC %includePaths%
call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64
set linkerflags= user32.lib gdi32.lib /subsystem:console /OUT:%arg1%.exe
mkdir build
pushd build
cl %compilerflags% ..\src\main.cpp /link %linkerflags%
popd
