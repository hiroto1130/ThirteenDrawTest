#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9tex.h>

#include "DrawTexture.h"
#include "class.h"

const int D3DFVF_CUSTOMVERTEX(D3DFVF_XYZRHW | D3DFVF_TEX1);//(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

void Draw(float x, float y, float width, float height, float tu, float tv, float tu_width, float tv_height, LPDIRECT3DTEXTURE9* Texture, DirectX directX)
{

	CUSTOMVERTEX customvertex[4] = {
	{x        ,y         ,0,1,tu           ,tv            },
	{x + width,y         ,0,1,tu + tu_width,tv            },
	{x + width,y + height,0,1,tu + tu_width,tv + tv_height},
	{x        ,y + height,0,1,tu           ,tv + tv_height},
	};

	directX.pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	directX.pDevice->SetTexture(0, *Texture);
	directX.pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customvertex, sizeof(CUSTOMVERTEX));

}

void DrawTest(float x, float y, float width, float height, float tu, float tv, float tu_width, float tv_height, LPDIRECT3DTEXTURE9* Texture, DirectX directX)
{

	CUSTOMVERTEX customvertex[4] = {
	{x        ,y         ,0,1,tu      ,tv            },
	{x + width,y         ,0,1,tu_width,tv            },
	{x + width,y + height,0,1,tu_width,tv_height},
	{x        ,y + height,0,1,tu      ,tv_height},
	};

	directX.pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	directX.pDevice->SetTexture(0, *Texture);
	directX.pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customvertex, sizeof(CUSTOMVERTEX));

}

void DrawEx(float x, float y, float width, float height, LPDIRECT3DTEXTURE9* Texture, DirectX directX)
{

	CUSTOMVERTEX customvertex[4] = {
	{x        ,y         ,  0, 1.0f,0.0f, 0.0f},
	{x + width,y         ,  0, 1.0f,1.0f, 0.0f},
	{x + width,y + height,  0, 1.0f,1.0f, 1.0f},
	{x        ,y + height,  0, 1.0f,0.0f, 1.0f},
	};

	directX.pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	directX.pDevice->SetTexture(0, *Texture);
	directX.pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customvertex, sizeof(CUSTOMVERTEX));

}

void LoadTexture(const char* file_name, LPDIRECT3DTEXTURE9* Texture, int texture_number, DirectX* directX) 
{
	HRESULT result = D3DXCreateTextureFromFile(directX->pDevice, file_name, Texture);

	if ((_D3DXERR)result == D3DXERR_INVALIDDATA)
	{
		OutputDebugString(TEXT("\nテクスチャファイルが見つかりません\n"));
	}
}

///////////////////////////////////////////////////////////////////////////////////////

#define MAP_SIZE_WIDTH (28)	
#define MAP_SIZE_HEIGHT (20)

void DrawMap(MapChipData MapData, DirectX* directX, LPDIRECT3DTEXTURE9* Texture)
{
	float cy = MapData.chip_y / MapData.Texture_Height;// 高さ
	float cx = MapData.chip_x / MapData.Texture_Widht; // 横
	float cx_size = MapData.MapChipWidht / MapData.Texture_Widht;
	float cy_size = MapData.MapChipHeight / MapData.Texture_Height;

	float cu_add = cx + cx_size;
	float cv_add = cy + cy_size;

	CUSTOMVERTEX sprite[] =
	{
		{ MapData.x                       , MapData.y                        , 0.0f, 1.0f,cx      ,cy      },
		{ MapData.x + MapData.MapChipWidht, MapData.y                        , 0.0f, 1.0f,cu_add  ,cy      },
		{ MapData.x + MapData.MapChipWidht, MapData.y + MapData.MapChipHeight, 0.0f, 1.0f,cu_add  ,cv_add  },
		{ MapData.x                       , MapData.y + MapData.MapChipHeight, 0.0f, 1.0f,cx      ,cv_add  },
	};

	directX->pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	directX->pDevice->SetTexture(0, *Texture);
	directX->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, sprite, sizeof(CUSTOMVERTEX));
}

void DrawMapChip(DirectX* directX, MapChipData MapData, LPDIRECT3DTEXTURE9* Texture, int MapChipList[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH])
{
	for (int i = 0; i < MapData.Map_HeigjtNumber; i++)
	{
		for (int j = 0; j < MapData.Map_WidhtNumber; j++)
		{
			int chip_id = MapChipList[i][j];
			if (MapChipList[i][j] == 3)
			{
				directX->a = directX->a + 1;
			}
		    int width_num = MapData.Texture_Widht / MapData.MapChipWidht;
			int height_num = MapData.Texture_Height / MapData.MapChipHeight;

			float chip_pos_x = (float)((chip_id % width_num) * MapData.MapChipWidht);
			float chip_pos_y = (float)((chip_id / height_num) * MapData.MapChipHeight);

			// 描画する場所の指定 // 
			MapData.chip_x = chip_pos_x;
			MapData.chip_y = chip_pos_y;
			// チップ指定 //
			MapData.x = MapData.MapChipWidht * j + 80;
			MapData.y = MapData.MapChipHeight * i + 80;

			DrawMap(MapData, directX, Texture);

		}

	}

	directX->a = 0;
}

