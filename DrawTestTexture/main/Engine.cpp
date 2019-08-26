#include "class.h"
#include "window.h"
#include "Device.h"
#include "Engine.h"

// ポインタ宣言をまとめたクラス
//Pointa Point;

HWND *InitEngine(int width, int height, HINSTANCE hInst, Pointa* point)
{
	//	window生成
	//HWND wind_handle = Make_WndFull(hInst,width,height);
	HWND hWnd = NULL;
	static CHAR szAppName[] = "Pac_Man";
	FLOAT wnd_width = width;
	FLOAT wnd_height = height;
	OutputWindow(&hWnd, &hInst, szAppName, &wnd_width, &wnd_height);

	if (FAILED(BuildDxDevice(&hWnd, point)))
	{

		return 0;

	}
	return &hWnd;
}

void EndEngine(Pointa point)
{
	// テクスチャの開放もする

	/*for (int a = 0; a < TextureList::MaxTexture; a++)
	{
		point.pTexture[a]->Release();
		point.pTexture[a] = nullptr;
	}*/

	if (point.pDinput != nullptr)
	{
		point.pDinput->Release();
		point.pDinput = nullptr;
	}
	if (point.pkey != nullptr)
	{
		point.pkey->Release();
		point.pkey = nullptr;
	}
}

bool DrawStart(Pointa* point)
{
	point->pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0f, 0);

	point->pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	point->pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	point->pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (D3D_OK == point->pDevice->BeginScene())
	{
		return true;
	}

	return false;
}

void UpdateInput(Pointa* point)
{
	UpdateKeyStatus(point);
}