#ifndef _GAMESCENE_H_ 
#define _GAMESCENE_H_


SceneId GameSceneMain(DirectX* directX, VariableNumber* var, Count* count);

void DrawGameScene(DirectX* directX, MapChipData Mapdata, VariableNumber* var);

class MainChar
{
public:
	int m_PosX = 80;
	int m_PosY = 80;
	float DrawSize = 40;
	float m_PosTu      = (float) 40 / 1024;
	float m_PosTu_Size = (float) 80 / 1024;
	float m_PosTv      = (float)  0 / 512;
	float m_PosTv_Size = (float) 40 / 512;

	float Add_TvSize;
	void InputTv(int Tv,int Tv_Size);
};

class Enemy_Green
{
public:

	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu      = (float)  0 / 1024;
	float m_PosTu_Size = (float) 40 / 1024;
	float m_PosTv      = (float) 40 / 512;
	float m_PosTv_Size = (float) 80 / 512;

	int DrawFlag = 0;

};

class Enemy_White
{
public:

	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu      = (float)  40 / 1024;
	float m_PosTu_Size = (float) 80 / 1024;
	float m_PosTv      = (float)   40 / 512;
	float m_PosTv_Size = (float)  80 / 512;

	int DrawFlag = 0;

};

class Meteorite
{
public:
	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu   = (float) 80 /1024;
	float m_Tu_Size = (float) 120 / 1024;
	float m_Postv   = (float)  40 / 512;
	float m_Tv_Size = (float)  80 / 512;
};

class Bullet
{
public:
	bool ShotFlag = false;
	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu      = (float)  0 / 1024;
	float m_PosTu_Size = (float) 40 / 1024;
	float m_PosTv      = (float)   0 / 512;
	float m_PosTv_Size = (float)  40 / 512;

	float BulletCount = 0;

};

class KeyState
{
public:
	int Move;
	int Shot;
};


class BeamSide
{
public:
	bool BeamSideFlag = false;
	float m_PosX;
	float m_PosY;
	float m_DrawSizeWidth = 1280;
	float m_DrawSizeHight = 120;
	float m_PosTu      = 0 / 2048;
	float m_PosTu_Size = 1120 / 2048; 

	float m_PosTv      = (float)  120 / 1024;
	float m_PosTv_Size = (float)  240 / 1024;
	void InputSidePosTv(float Tv, float TvSize);

	float m_Add_Tv_Size = (float) 120 / 1024;
};

class BeamVerticality
{
public:
	bool BeamVerticalityeFlag = false;
	float m_PosX;
	float m_PosY;
	float m_DrawSizeWidth = 120;
	float m_DrawSizeHight = 960;

	float m_PosTu      = (float)  120 / 1024;
	float m_PosTu_Size = (float)  240 / 1024;
	void InputVerticalityPosTv(float Tv, float TvSize);
	
	float m_Add_Tu_Size = (float)120 / 1024;
	float m_PosTv      = 0;
	float m_PosTv_Size = 1;
};

class Star
{
public:
	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu      = (float)   0 / 1024;
	float m_PosTu_Size = (float)  40 / 1024;
	float m_PosTv      = (float)  80 /  512;
	float m_PosTv_Size = (float) 120 /  512;
	bool DrawFlag = false;

};

#endif