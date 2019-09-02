#ifndef ENGINE_H
#define ENGINE_H

#include "class.h"

//Pointa Point;

HWND* InitEngine(int width, int height, HINSTANCE hInst, DirectX* directX);

void EndEngine(DirectX directX);

bool DrawStart(DirectX* directX);

void UpdateInput(DirectX* directX);

#endif // !1