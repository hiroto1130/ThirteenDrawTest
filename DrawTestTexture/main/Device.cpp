#include "class.h" 

//Pointa point;
HRESULT InitDinput(HWND*, Pointa*);
HRESULT InitD3d(HWND*, Pointa*);

// キーボード //
static const int MAX_KEY_NUMBER = 256;
// 入力キーを入れる値
BYTE KeyState[MAX_KEY_NUMBER];
// 256の配列を持つ
const int MASK_NUM = 0x80;

HRESULT BuildDxDevice(HWND *hInst, Pointa* point)
{
	//// InitD3d が初期化されているかどうか ////
	if (FAILED(InitD3d(hInst, point)))
	{
		return E_FAIL;
	}

	//// InitDinput 初期化されているかどうか ////
	if (FAILED(InitDinput(hInst, point)))
	{
		return E_FAIL;
	}

	//D3Dのポインタ変数にDirect3DCreate9関数(Direct3Dを作る関数)で作成したものを代入
	//point->pDirect3d = Direct3DCreate9(D3D_SDK_VERSION);

	//// Direct3DCreate9 が ////
	if (point->pDirect3d == NULL)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT InitD3d(HWND *hInst, Pointa* point)
{
	if (NULL == (point->pDirect3d = Direct3DCreate9(D3D_SDK_VERSION)))
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

	if (FAILED(point->pDirect3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *hInst,
		D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &point->pDevice)))
	{
		return E_FAIL;
	}

	return S_OK;

}

////// directinput //////

HRESULT InitDinput(HWND* hInst, Pointa* point)
{
	HRESULT hr;

	//// DirectInput8の作成 ////
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID * *)& point->pDinput, NULL)))
	{
		return hr;
	}

	//// InputDeviceを作成 ////         * どの入力デバイスから情報を受け取るか
	if (FAILED(hr = point->pDinput->CreateDevice(GUID_SysKeyboard, &point->pkey, NULL)))
	{
		return hr;
	}

	//// デバイスのフォーマット設定,形式 ////　　　* キーボード c_dfDIKeyboard マウス c_dfDIMouse
	if (FAILED(hr = point->pkey->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}

	//// 協調レベルを設定 ////    * フォアグラウンド、バックグラウンド 排他的、非排他的 
	if (FAILED(hr = point->pkey->SetCooperativeLevel(*hInst, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}

	//// 権限の取得 ////
	point->pkey->Acquire();

	return S_OK;
}

////// キーステータス更新関数 //////
void UpdateKeyStatus(Pointa* point)
{
	HRESULT hr = point->pkey->Acquire();

	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		point->pkey->GetDeviceState(sizeof(KeyState), &KeyState);
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