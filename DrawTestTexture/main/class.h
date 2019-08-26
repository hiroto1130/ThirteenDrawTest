#ifndef CLASS_H
#define CLASS_H

#include<stdio.h>
#include<windows.h>
#include<d3dx9.h>
#include<tchar.h>
#include<dinput.h>

const int TEXTUREMAX(10);

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

//enum TextureList
//{
//	TitleSceneTexture,
//	SetSceneBackTexture,
//	SelectGametexture,
//	OptionSceneTexture,
//	GameSceneTexture,
//	MapChipTexture,
//	ResultSceneTexture,
//	MaxTexture
//};

class Pointa
{
public:

	int a = 0;
	LPDIRECT3D9 pDirect3d;
	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECTINPUT8 pDinput;
	LPDIRECTINPUTDEVICE8 pkey;


};

// テクスチャデータ
struct TEXTUREDATA
{

	LPDIRECT3DTEXTURE9 m_pTexture[TEXTUREMAX];  // テクスチャ情報
	float m_Width;					// テクスチャの幅
	float m_Height;					// テクスチャの高さ

};

// マップチップでの画像数
enum MAPCHIP_TEXTURE_ID
{
	Non = -1,		// 無し
	MapChip,		// マップチップ	
	MaxTextureId	// 最大数
};

class VariableNumber
{
public:
	int SceneSelect;
	int count = 0;
	int PreviousKeyState = 0;
	int temp;
	float MoveSpeed = 4;
	float with;
	float hight;
	float BeamState;
	float MeteoriteState;
	float MeteoriteDrawState;
	float MeteoriteDrawState2;
	float EnemyState;
	float EnemyDrawState;

};

class Count
{
public:
	int Frame = 0;
	void FrameReset() { Frame = 0; }

	int Frame2 = 0;
	void Flame2Reset() { Frame2 = 0; }

	int Frame3 = 0;
	void Frame3Reset() { Frame3 = 0; }

	int Frame4 = 0;
	void Frame4Reset() { Frame4 = 0; }

	int Frame5 = 0;
	void Frame5Reset() { Frame5 = 0; }

	int Frame6 = 0;
	void Frame6Reset() { Frame6 = 0; }

	int Frame7 = 0;
	void Frame7Reset() { Frame7 = 0; }

	int Frame8 = 0;
	void Frame8Reset() { Frame7 = 0; }

	int Frame9 = 0;
	void Frame9Reset() { Frame7 = 0; }

	int Frame10 = 0;
	void Frame10Reset() { Frame10 = 0; }
	void AllReset()
	{
		Frame = 0;
		Frame2 = 0;
		Frame3 = 0;
		Frame4 = 0;
		Frame5 = 0;
		Frame6 = 0;
		Frame7 = 0;
	}
};

// extern VariableNumber var;

// SceneId の数
enum SceneId
{
	TitleScene,			//!< タイトルシーン
	SetScene,			//!< 難易度設定シーン
	OptionScene,        //!< ヘルプ(遊戯説明画面)シーン
	GameScene,			//!< ゲーム本編シーン
	ResultScene,		//!< リザルトシーン
	SceneIdMax,			//!< シーンID最大
};

// Step 数
enum SceneStep
{
	InitStep,			//!< 初期化
	MainStep,			//!< メイン
	EndStep,			//!< 終了
};

enum TitleTextureList
{
	MainTitleTexture,
	RogTexture,
	MaxTitleTexture,

};

enum SetTextureList
{
	MaxSetTexture,
};

enum OptionTextureList
{
	MaxOptionTexture,
};

enum GameTextureList
{
	BackTexture,
	ChraTexture,
	MapChipTexture,
	BeamSideTextutre,
	BeamVerticalityTexture,
	MaxGameTexture,
};

enum ResultTextureList
{
	MainResultTexture,
	MainResultTexture2,
	MainResultTexture3,
	MainResultTexture4,
	MainResultTexture5,
	MainResultTexture6,
	MaxResultTexture,
};


//共通のインスタンス
extern Pointa point;

class MapChipData
{
public:
	int Map_HeigjtNumber = 20;
	int Map_WidhtNumber = 28;
	float MapChipHeight = 40;
	float MapChipWidht = 40;
	float Texture_Height = 256;
	float Texture_Widht = 256;
	float x;
	float y;
	float chip_x;
	float chip_y;
	/*void draw_point(int a, int b);
	void draw_chip(int a, int b);*/
};

//void MapChipData::draw_point(int a, int b)
//{
//	x = a;
//	y = b;
//};
//
//void MapChipData::draw_chip(int a, int b)
//{
//	chip_x = a;
//	chip_y = b;
//};


extern MapChipData MapData;
#endif // !