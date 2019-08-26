#include<d3dx9.h>
#include<tchar.h>
#include<dinput.h>

#include "window.h"
#include "class.h"

////// ウィンドウプロシージャー //////

LRESULT CALLBACK wndProc(HWND hInst, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch ((CHAR)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}

	return DefWindowProc(hInst, iMsg, wParam, lParam);
}


/**

*@fn HWND Make_Wnd(HINSTANCE hInst, int width, int height)
* ウィンドウの初期化、生成関数
* @param hInst  インスタントハンドル
* @param width  ウィンドウの幅の値
* @param height ウィンドウの高さの値
* @return デバイス作成用のインスタントハンドルを返す

*/

//  window用
HWND Make_Wnd(HINSTANCE hInst, int width, int height)
{
	////////////////////////// ウィンドウ初期化 //////////////////////////////

	static char szAppName[] = "TEST";
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = wndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//////////////////////////// ウィンドウ生成 //////////////////////////

	RegisterClassEx(&wndclass);
	HWND hInsT = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, hInst, NULL);

	RECT rx; //ウィンドウ領域
	RECT cx; //クライアント領域
	GetWindowRect(hInsT, &rx);
	GetClientRect(hInsT, &cx);
	const int new_width = width + (rx.right - rx.left) - (cx.right - cx.left);
	const int new_height = height + (rx.bottom - rx.top) - (cx.bottom - cx.top);
	const int disp_width = GetSystemMetrics(SM_CXSCREEN);
	const int disp_height = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(hInsT, NULL, (disp_width - new_width) / 2,
		(disp_height - new_height) / 2,
		new_width, new_height, SWP_SHOWWINDOW);

	ShowWindow(hInsT, SW_SHOW);
	UpdateWindow(hInsT);

	return hInsT;
}

// フルスクリーンモード用
HWND Make_WndFull(HINSTANCE hInst, int width, int height)
{
	////////////////////////// ウィンドウ初期化 //////////////////////////////

	static char szAppName[] = "TEST";
	WNDCLASSEX wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = wndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//////////////////////////// ウィンドウ生成 //////////////////////////

	RegisterClassEx(&wndclass);
	HWND hInsT = CreateWindow(szAppName, szAppName, WS_VISIBLE | WS_POPUP, 0, 0, width, height, NULL, NULL, hInst, NULL);

	//ShowWindow(hInsT, SW_SHOW);
	//UpdateWindow(hInsT);

	return hInsT;
}

HWND OutputWindow(HWND * hWnd, HINSTANCE * hInstance, const TCHAR * API_NAME, FLOAT * wnd_width, FLOAT * wnd_height)
{
	// Wndclassの初期化
	WNDCLASS Wndclass;
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;											// ウィンドウスタイル
	Wndclass.lpfnWndProc = wndProc;																// ウィンドウプロシージャ
	Wndclass.cbClsExtra = 0;																				// メモリ確保
	Wndclass.cbWndExtra = 0;																			// メモリ確保
	Wndclass.hInstance = *hInstance;																// ハンドルインスタンス
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);									// アイコン
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);										// カーソル
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);			// 背景のブラシ,色
	Wndclass.lpszMenuName = NULL;																// メニュー画面の名前
	Wndclass.lpszClassName = API_NAME;															// アプリケーションの名前

	// ウィンドウクラスの登録

	// ウィンドウハンドルにcreatewindow関数で作った情報を代入
	RegisterClass(&Wndclass);

	*hWnd = CreateWindow(API_NAME, API_NAME, WS_OVERLAPPEDWINDOW, 0, 0, *wnd_width, *wnd_height, NULL, NULL, *hInstance, NULL);

	RECT rx; //ウィンドウ領域
	RECT cx; //クライアント領域
	GetWindowRect(*hWnd, &rx);
	GetClientRect(*hWnd, &cx);
	const int new_width = *wnd_width + (rx.right - rx.left) - (cx.right - cx.left);
	const int new_height = *wnd_height + (rx.bottom - rx.top) - (cx.bottom - cx.top);
	const int disp_width = GetSystemMetrics(SM_CXSCREEN);
	const int disp_height = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(*hWnd, NULL, (disp_width - new_width) / 2,
		(disp_height - new_height) / 2,
		new_width, new_height, SWP_SHOWWINDOW);

	ShowWindow(*hWnd, SW_SHOW);
	UpdateWindow(*hWnd);

	return *hWnd;
}