#include "class.h" 

//DirectX* directX;
HRESULT InitDinput(HWND*, DirectX*);
HRESULT InitD3d(HWND*, DirectX*);

// キーボード //
static const int MAX_KEY_NUMBER = 256;
// 入力キーを入れる値
BYTE KeyState[MAX_KEY_NUMBER];
// 256の配列を持つ
const int MASK_NUM = 0x80;

HRESULT BuildDxDevice(HWND *hInst, DirectX* directX)
{
	//// InitD3d が初期化されているかどうか ////
	if (FAILED(InitD3d(hInst, directX)))
	{
		return E_FAIL;
	}

	//// InitDinput 初期化されているかどうか ////
	if (FAILED(InitDinput(hInst, directX)))
	{
		return E_FAIL;
	}

	//D3Dのポインタ変数にDirect3DCreate9関数(Direct3Dを作る関数)で作成したものを代入
	//point->pDirect3d = Direct3DCreate9(D3D_SDK_VERSION);

	//// Direct3DCreate9 が ////
	if (directX->pDirect3d == NULL)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT InitD3d(HWND *hInst, DirectX* directX)
{
	if (NULL == (directX->pDirect3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	//// バッファ設定 ////

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;

	//// デバイス生成 ////

	if (FAILED(directX->pDirect3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *hInst,
		D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &directX->pDevice)))
	{
		return E_FAIL;
	}

	return S_OK;

}

////// directinput //////

HRESULT InitDinput(HWND* hInst, DirectX* directX)
{
	HRESULT hr;

	//// DirectInput8の作成 ////
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID * *)& directX->pDinput, NULL)))
	{
		return hr;
	}

	//// InputDeviceを作成 ////         * どの入力デバイスから情報を受け取るか
	if (FAILED(hr = directX->pDinput->CreateDevice(GUID_SysKeyboard, &directX->pkey, NULL)))
	{
		return hr;
	}

	//// デバイスのフォーマット設定,形式 ////　　　* キーボード c_dfDIKeyboard マウス c_dfDIMouse
	if (FAILED(hr = directX->pkey->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	//// 協調レベルを設定 ////    * フォアグラウンド、バックグラウンド 排他的、非排他的 
	if (FAILED(hr = directX->pkey->SetCooperativeLevel(*hInst, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}

	//// 権限の取得 ////
	directX->pkey->Acquire();

	return S_OK;
}

////// キーステータス更新関数 //////
void UpdateKeyStatus(DirectX* directX)
{
	HRESULT hr = directX->pkey->Acquire();

	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		directX->pkey->GetDeviceState(sizeof(KeyState), &KeyState);
	}

}

////// キー入力関数 //////
bool GetKeyStatus(int KeyNumber)
{

	if (KeyState[KeyNumber] & MASK_NUM)
	{

		return true;// 入力されたら true を返す

	}
	return false;// 入力されていなければ false を返す

}