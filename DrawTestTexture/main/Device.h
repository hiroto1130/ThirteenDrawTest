#ifndef DEVICE_H
#define DEVICE_H

#include "class.h"

HRESULT BuildDxDevice(HWND *hInst, DirectX* directX);

void UpdateKeyStatus(DirectX* directX);

bool GetKeyStatus(int KeyNumber);

#endif // !1