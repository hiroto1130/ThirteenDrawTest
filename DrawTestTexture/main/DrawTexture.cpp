#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9tex.h>

#include "DrawTexture.h"
#include "class.h"

const int D3DFVF_CUSTOMVERTEX(D3DFVF_XYZRHW | D3DFVF_TEX1);//(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//struct TEXTUREDATA
//{
//
//	LPDIRECT3DTEXTURE9 m_pTexture;  // テクスチャ情報
//	float m_Width;					// テクスチャの幅
//	float m_Height;					// テクスチャの高さ
//
//};
//
//TEXTUREDATA pTexture;

void Draw(float x, float y, float width, float height, float tu, float tv, float tu_width, float tv_height, LPDIRECT3DTEXTURE9* Texture, Pointa point)
{

	CUSTOMVERTEX customvertex[4] = {
	{x        ,y         ,0,1,tu           ,tv            },
	{x + width,y         ,0,1,tu + tu_width,tv            },
	{x + width,y + height,0,1,tu + tu_width,tv + tv_height},
	{x        ,y + height,0,1,tu           ,tv + tv_height},
	};

	point.pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	point.pDevice->SetTexture(0, *Texture);
	point.pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customvertex, sizeof(CUSTOMVERTEX));

}

void DrawTest(float x, float y, float width, float height, float tu, float tv, float tu_width, float tv_height, LPDIRECT3DTEXTURE9* Texture, Pointa point)
{

	CUSTOMVERTEX customvertex[4] = {
	{x        ,y         ,0,1,tu      ,tv            },
	{x + width,y         ,0,1,tu_width,tv            },
	{x + width,y + height,0,1,tu_width,tv_height},
	{x        ,y + height,0,1,tu      ,tv_height},
	};

	point.pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	point.pDevice->SetTexture(0, *Texture);
	point.pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customvertex, sizeof(CUSTOMVERTEX));

}

void DrawEx(float x, float y, float width, float height, LPDIRECT3DTEXTURE9* Texture, Pointa point)
{

	CUSTOMVERTEX customvertex[4] = {
	{x        ,y         ,  0, 1.0f,0.0f, 0.0f},
	{x + width,y         ,  0, 1.0f,1.0f, 0.0f},
	{x + width,y + height,  0, 1.0f,1.0f, 1.0f},
	{x        ,y + height,  0, 1.0f,0.0f, 1.0f},
	};

	point.pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	point.pDevice->SetTexture(0, *Texture);
	point.pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customvertex, sizeof(CUSTOMVERTEX));

}

//void LoadTexture(const char* file_name, LPDIRECT3DTEXTURE9* Texture, int texture_number,Pointa* point) {
//	HRESULT result = D3DXCreateTextureFromFileEx(point->pDevice, file_name, 1920, 1080, 0, 0, D3DFMT_UNKNOWN,
//		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
//		0xff000000, NULL, NULL, Texture);
//
//	if ((_D3DXERR)result == D3DXERR_INVALIDDATA)
//	{
//		OutputDebugString(TEXT("\nテクスチャファイルが見つかりません\n"));
//	}
//}

void LoadTexture(const char* file_name, LPDIRECT3DTEXTURE9* Texture, int texture_number, Pointa* point) {
	HRESULT result = D3DXCreateTextureFromFile(point->pDevice, file_name, Texture);

	if ((_D3DXERR)result == D3DXERR_INVALIDDATA)
	{
		OutputDebugString(TEXT("\nテクスチャファイルが見つかりません\n"));
	}
}

///////////////////////////////////////////////////////////////////////////////////////

#define MAP_SIZE_WIDTH (28)	
#define MAP_SIZE_HEIGHT (20)

void DrawMap(MapChipData MapData, Pointa* point, LPDIRECT3DTEXTURE9* Texture)
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

	point->pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	point->pDevice->SetTexture(0, *Texture);
	point->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, sprite, sizeof(CUSTOMVERTEX));
}

void DrawMapChip(Pointa* point, MapChipData MapData, LPDIRECT3DTEXTURE9* Texture, int MapChipList[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH])
{
	for (int i = 0; i < MapData.Map_HeigjtNumber; i++)
	{
		for (int j = 0; j < MapData.Map_WidhtNumber; j++)
		{
			int chip_id = MapChipList[i][j];
			if (MapChipList[i][j] == 3)
			{
				point->a = point->a + 1;
			}
			int width_num = MapData.Texture_Widht/*256*/ / MapData.MapChipWidht/*40*/;
			int height_num = MapData.Texture_Height/*256*/ / MapData.MapChipHeight/*40*/;

			float chip_pos_x = (float)((chip_id % width_num) * MapData.MapChipWidht/*40*/);
			float chip_pos_y = (float)((chip_id / height_num) * MapData.MapChipHeight/*40*/);

			// 描画する場所の指定 // 
			MapData.chip_x = chip_pos_x;
			MapData.chip_y = chip_pos_y;
			// チップ指定 //
			MapData.x = MapData.MapChipWidht * j + 80;
			MapData.y = MapData.MapChipHeight * i + 80;

			DrawMap(MapData, point, Texture);

		}

	}

	point->a = 0;
}

/*
#ifndef DRAW_H
#define DRAW_H

#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9tex.h>


typedef struct
{
	float	// 頂点座標
		x,  // 幅
		y,  // 高さ
		z;  // 奥行

	float   // 除算数
		rhw;

	float   // テクスチャ座標
		tu,  // 幅
		tv;	// 高さ
} CUSTOMVERTEX, * P_CUSTOMVERTEX;

class MapChipData
{
public:
	const int Map_HeightNumber = 10;
	const int Map_WidhtNumber  = 10;

	float MapChipHeight;
	float MapChipWidht;
	void InputChipSize(int Height,int Widht)
	{
		MapChipHeight = Height;
		MapChipWidht = Widht;
	}

	float Texture_Height;
	float Texture_Widht;
	void InputTextureSize(int Height, int Widht)
	{
		Texture_Height = Height;
		Texture_Widht = Widht;
	}

	float x;
	float y;
	float chip_x;
	float chip_y;
};

#endif // !DRAW_H

#include"Draw.h"
#include"Scene.h"

MapChipData chipdata;
static LPDIRECT3DDEVICE9 pDevice;

// テクスチャ保存用構造体
struct TEXTUREDATA
{

	LPDIRECT3DTEXTURE9 pTexture;  // テクスチャ情報
	float Width;					// テクスチャの幅
	float Height;					// テクスチャの高さ

};

static TEXTUREDATA** TextureData[MAXSCENE] = { 0 };

// 画像読み込み関数
void LoadTexture(const char* file_name, int SelectScene, int  SelectTexture)
{
	HRESULT result = D3DXCreateTextureFromFile(pDevice, file_name, &TextureData[SelectScene][SelectTexture]->pTexture);

	if ((_D3DXERR)result == D3DXERR_INVALIDDATA)
	{
		OutputDebugString(TEXT("\nテクスチャファイルが見つかりません\n"));
	}

}


// 描画関数　前処理、後処理作成必要
void Draw(float x, float y, float Texturewidth, float Textureheight, float tu, float tv, float tu_width, float tv_height, TEXTUREDATA* TextureData)
{

	CUSTOMVERTEX customvertex[4] = {
	{x               ,y                ,0,1,tu      ,tv         },
	{x + Texturewidth,y                ,0,1,tu_width,tv         },
	{x + Texturewidth,y + Textureheight,0,1,tu_width,tv_height  },
	{x               ,y + Textureheight,0,1,tu      ,tv_height  },
	};

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	pDevice->SetTexture(0, TextureData->pTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customvertex, sizeof(CUSTOMVERTEX));

}

//	リリース(開放)関数
void TextureRelease(int SelectScene, int MaxTexture)
{
	for (int a = 0; a < MaxTexture; a++)
	{
		TextureData[SelectScene][a]->pTexture->Release();
		TextureData[SelectScene][a]->pTexture = nullptr;
	}
}

//画像描画
////////////////////////////////////////////////////////////////////////////////////////////////////////
//マップチップ描画

void DrawMap(MapChipData MapData, TEXTUREDATA * TextureData)
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

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	pDevice->SetTexture(0, TextureData->pTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, sprite, sizeof(CUSTOMVERTEX));
}

void DrawMapChip(MapChipData MapData, int MapChipList[10][10], TEXTUREDATA * TextureData)
{
	for (int i = 0; i < MapData.Map_HeightNumber; i++)
	{
		for (int j = 0; j < MapData.Map_WidhtNumber; j++)
		{
			int chip_id = MapChipList[i][j];
			if (chip_id == 0)
			{
				continue;
			}

			int width_num = MapData.Texture_Widht / MapData.MapChipWidht;
			int height_num = MapData.Texture_Height / MapData.MapChipHeight;

			float chip_pos_x = (float)((chip_id % width_num) * MapData.MapChipWidht);
			float chip_pos_y = (float)((chip_id / height_num) * MapData.MapChipHeight);

			// 描画する場所の指定 //
			MapData.chip_x = chip_pos_x;
			MapData.chip_y = chip_pos_y;
			// チップ指定 //
			MapData.x = MapData.MapChipWidht * j;
			MapData.y = MapData.MapChipHeight * i;

			DrawMap(MapData, TextureData);

		}
	}
}
*/