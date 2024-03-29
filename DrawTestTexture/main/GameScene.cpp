﻿#include<stdio.h>
#include<time.h>
#include<random>
#include <random>
#include <iostream>

#include"Scene.h"
#include"class.h"
#include"DrawTexture.h"
#include"Device.h"
#include"GameScene.h"
#include"Gamesystem.h"


extern int g_SceneStep;
void DrawGameScene(DirectX* directX, MapChipData MapData, VariableNumber* var);
void InitGameScene(DirectX* directX);
void UpdateGameScene(Count* count, VariableNumber* var);
SceneId FinisGameScene();
int* MAPR[22];

TEXTUREDATA GameTextureData;

#define MAP_SIZE_WIDTH (28)	
#define MAP_SIZE_HEIGHT (20)

int MapChipList[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH]
{

	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

};



SceneId GameSceneMain(DirectX* directX, VariableNumber* var, Count* count)
{
	switch (GetCurrentSceneStep())
	{
		// 初期化
	case SceneStep::InitStep:
		count->AllReset();
		InitGameScene(directX);
		break;
		// 本編
	case SceneStep::MainStep:
		UpdateGameScene(count,var);
		break;
		// 終了
	case SceneStep::EndStep:
		return FinisGameScene();
	}
	return SceneId::GameScene;
}

BeamSide beamSide;
BeamVerticality  beamVerticality;
Bullet bullet[5];
Meteorite meteorite[8];
Enemy_Green e_green[2];
Enemy_White e_white[2];
MainChar mainChar;
KeyState keyState;
Star star[12];

void DrawGameScene(DirectX* directX, MapChipData MapData,VariableNumber* var)
{
	// 背景
	DrawTest( 0, 0, 1280, 960, 0, 0, 1, 1, &GameTextureData.m_pTexture[GameTextureList::BackTexture], *directX);
	// マップチップ
	DrawMapChip(directX, MapData, &GameTextureData.m_pTexture[GameTextureList::MapChipTexture], MapChipList);
	// 自キャラ 操作キャラ
	DrawTest(mainChar.m_PosX, mainChar.m_PosY, mainChar.DrawSize, mainChar.DrawSize, mainChar.m_PosTu, mainChar.m_PosTv, mainChar.m_PosTu_Size, mainChar.m_PosTv_Size, &GameTextureData.m_pTexture[GameTextureList::ChraTexture], *directX);
	
	
	if (var->EnemyDrawState == 1)
	{
		for (int a = 0; a < 2; a++)
		{
			if (e_green[a].DrawFlag == 1)
			{
				// 敵1 緑敵
				DrawTest(e_green[a].m_PosX, e_green[a].m_PosY, e_green[a].m_DrawSize, e_green[a].m_DrawSize, e_green[a].m_PosTu, e_green[a].m_PosTv, e_green[a].m_PosTu_Size, e_green[a].m_PosTv_Size, &GameTextureData.m_pTexture[GameTextureList::ChraTexture], *directX);
			}
			if (e_white[a].DrawFlag == 1)
			{
				// 敵2 紫敵
				DrawTest(e_white[a].m_PosX, e_white[a].m_PosY, e_white[a].m_DrawSize, e_white[a].m_DrawSize, e_white[a].m_PosTu, e_white[a].m_PosTv, e_white[a].m_PosTu_Size, e_white[a].m_PosTv_Size, &GameTextureData.m_pTexture[GameTextureList::ChraTexture], *directX);

			}
		}
	}
	

	// メテオ(第一弾)
	if (var->MeteoriteDrawState == 1)
	{
			for (int a = 0; a < 4; a++)
			{
				DrawTest(meteorite[a].m_PosX, meteorite[a].m_PosY, meteorite[a].m_DrawSize, meteorite[a].m_DrawSize, meteorite[a].m_PosTu, meteorite[a].m_Postv, meteorite[a].m_Tu_Size, meteorite[a].m_Tv_Size, &GameTextureData.m_pTexture[GameTextureList::ChraTexture], *directX);
			}
		
	}

	// メテオ(第二弾)
	if (var->MeteoriteDrawState2 == 1)
	{
		for (int a = 4; a < 8; a++)
		{
			DrawTest(meteorite[a].m_PosX, meteorite[a].m_PosY, meteorite[a].m_DrawSize, meteorite[a].m_DrawSize, meteorite[a].m_PosTu, meteorite[a].m_Postv, meteorite[a].m_Tu_Size, meteorite[a].m_Tv_Size, &GameTextureData.m_pTexture[GameTextureList::ChraTexture], *directX);
		}

	}

	// ソゲキッ
	for (int a = 0; a < 5; a++)
	{
		if (bullet[a].ShotFlag == true)
		{
			DrawTest(bullet[a].m_PosX, bullet[a].m_PosY, bullet->m_DrawSize, bullet->m_DrawSize,bullet->m_PosTu, bullet->m_PosTv, bullet->m_PosTu_Size, bullet->m_PosTv_Size, &GameTextureData.m_pTexture[GameTextureList::ChraTexture], *directX);
		}
	}

	// ビーム横描画
	if (beamSide.BeamSideFlag == true)
	{
		DrawTest(beamSide.m_PosX, /**/beamSide.m_PosY, beamSide.m_DrawSizeWidth, beamSide.m_DrawSizeHight, beamSide.m_PosTu, beamSide.m_PosTv, beamSide.m_PosTu_Size, beamSide.m_PosTv_Size, &GameTextureData.m_pTexture[GameTextureList::BeamSideTextutre], *directX);
	}

	// ビーム縦描画
	if(beamVerticality.BeamVerticalityeFlag == true)
	{
		DrawTest(/**/beamVerticality.m_PosX, beamVerticality.m_PosY, beamVerticality.m_DrawSizeWidth, beamVerticality.m_DrawSizeHight, beamVerticality.m_PosTu, beamVerticality.m_PosTv, beamVerticality.m_PosTu_Size, beamVerticality.m_PosTv_Size, &GameTextureData.m_pTexture[GameTextureList::BeamVerticalityTexture], *directX);
	}

	// 星の描画(基本4つ、最大12)
	for (int a = 0; a < 12; a++)
	{
		if (star[a].DrawFlag == true)
		{
			DrawTest(star[a].m_PosX, star[a].m_PosY, star->m_DrawSize, star->m_DrawSize, star->m_PosTu, star->m_PosTv, star->m_PosTu_Size, star->m_PosTv_Size, &GameTextureData.m_pTexture[GameTextureList::ChraTexture], *directX);
		}
	}
}


// テクスチャ読み込み
void InitGameScene(DirectX* directX)
{
	LoadTexture("Texture/main_back.png", &GameTextureData.m_pTexture[GameTextureList::BackTexture], 0,           directX);
	LoadTexture("Texture/map_chip2.png", &GameTextureData.m_pTexture[GameTextureList::MapChipTexture], 0,        directX);
	LoadTexture("Texture/character.png", &GameTextureData.m_pTexture[GameTextureList::ChraTexture], 0,           directX);
	LoadTexture("Texture/beam_Side.png", &GameTextureData.m_pTexture[GameTextureList::BeamSideTextutre], 0,      directX);
	LoadTexture("Texture/beam_Ver.png", &GameTextureData.m_pTexture[GameTextureList::BeamVerticalityTexture], 0, directX);

	ChangeSceneStep(SceneStep::MainStep);
}

// 次のシーンに行くための条件記入
// ゲーム設定記入
void UpdateGameScene(Count* count, VariableNumber* var)
{
	FrameCount(count, &keyState);

	InptKeystate(count, &keyState, bullet);

	ChraMove(count, &keyState, &mainChar);

	CharTextureChange(count, &mainChar,bullet);

	HitJudge(&mainChar);

	SetBeam_first(count, var, MapChipList, &beamSide, &beamVerticality,1);

	DrawMeteorite(count, var, MapChipList, meteorite);

    DrawMeteoriteTwo(count, var, MapChipList, meteorite);

	EnemyMove(count, var, e_green, e_white);

	DrawEnemy(count, var, MapChipList, e_green, e_white);

	ShotMove(&keyState, bullet,&mainChar);

	ShotHitJudge(bullet, &keyState, &mainChar);

	StarDraw(star,count);

	HitBulletStar(&mainChar, star,count,&keyState);

	HitCharMeteorite(meteorite,&mainChar,count,&keyState);

	HitBulletStar(bullet,count,e_green,e_white,&keyState);

	if (GetKeyStatus(DIK_RETURN))
	{

		ChangeSceneStep(SceneStep::EndStep);
	}
}

// 次に飛ぶシーン先の設定
SceneId FinisGameScene()
{
	for (int a = 0; a < GameTextureList::MaxGameTexture; a++)
	{
		GameTextureData.m_pTexture[a]->Release();
		GameTextureData.m_pTexture[a] = nullptr;
	}
	// 次のシーンの遷移先IDを返す
	return SceneId::ResultScene;

}
