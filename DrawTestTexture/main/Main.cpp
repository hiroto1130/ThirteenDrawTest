 #include <Windows.h>
#include "window.h"
#include "Engine.h"
#include "Scene.h"
#include "class.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance,
	LPSTR lpCmpLine, INT nCmdShow)
{
	Pointa point;
	MapChipData MapData;
	VariableNumber variable;
	Count count;
	HWND* hWnd;

	// MapChipData MapData;
	if ((hWnd = InitEngine(1280, 960, hInst, &point)) == NULL)
	{
		return 0;
	}

	timeBeginPeriod(1);
	//今の時間をtimeに保存。
	DWORD time = timeGetTime();
	DWORD prevtime = 0;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		bool message_ret = false;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				break;
			}
			else
			{
				time = timeGetTime();
				if (time - prevtime < 1000 / 60)
				{
					
				}
				
				UpdateScene(&point, MapData, &variable, &count);
			}
			prevtime = time;
		}
		 timeEndPeriod(1);
	}

	// エンジン終了
	EndEngine(point);

	return 0;
}