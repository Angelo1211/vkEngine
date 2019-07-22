@echo off
set arg1=%1
call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64
set compilerflags=/Od /Zi /EHsc /FC
set linkerflags= user32.lib gdi32.lib /OUT:%arg1%.exe
mkdir build
pushd build
cl %compilerflags% ..\src\main.cpp /link %linkerflags%
popd
