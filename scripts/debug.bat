@echo off
set arg1=%1
call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64
devenv /NoSplash build\%arg1%.exe
