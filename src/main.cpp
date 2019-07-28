#include <stdio.h>
#define UNICODE
#define _DEBUG 1
#include <windows.h>

//Unity Build
#include "globals.cpp"
#include "renderer.cpp"
#include "win32Layer.cpp"

/*
PLAN:
---------------
*/

int
main(){
  return WinMain(GetModuleHandle(NULL), 0, 0, 0);
}
