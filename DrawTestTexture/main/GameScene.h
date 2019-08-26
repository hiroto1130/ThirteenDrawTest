#ifndef _GAMESCENE_H_ 
#define _GAMESCENE_H_


SceneId GameSceneMain(Pointa* point, VariableNumber* var, Count* count);

void DrawGameScene(Pointa* point, MapChipData Mapdata, VariableNumber* var);

class MainChar
{
public:
	int m_PosX = 80;
	int m_PosY = 80;
	float DrawSize = 40;
	float m_PosTu      = (float)  0 / 512;
	float m_PosTu_Size = (float) 40 / 512;
	float m_PosTv      = (float)  0 / 512;
	float m_PosTv_Size = (float) 40 / 512;
};

class Enemy_Green
{
public:

	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu      = (float) 40 / 512;
	float m_PosTu_Size = (float) 80 / 512;
	float m_PosTv      = (float)  0 / 512;
	float m_PosTv_Size = (float) 40 / 512;

};

class Enemy_White
{
public:

	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu      = (float)  80 / 512;
	float m_PosTu_Size = (float) 120 / 512;
	float m_PosTv      = (float)   0 / 512;
	float m_PosTv_Size = (float)  40 / 512;

};

class Meteorite
{
public:
	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu   = (float) 120 / 512;
	float m_Tu_Size = (float) 160 / 512;
	float m_Postv   = (float)   0 / 512;
	float m_Tv_Size = (float)  40 / 512;
};

class Bullet
{
public:
	bool ShotFlag = false;
	float m_PosX;
	float m_PosY;
	float m_DrawSize = 40;
	float m_PosTu      = (float) 160 / 512;
	float m_PosTu_Size = (float) 200 / 512;
	float m_PosTv      = (float)   0 / 512;
	float m_PosTv_Size = (float)  40 / 512;
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
	float m_DrawSizeWidth = 1200;
	float m_DrawSizeHight = 120;
	float m_PosTu      = (float)    0 / 2048;
	float m_PosTu_Size = (float) 2048 / 2048; 
	float m_PosTv      = (float)    0 / 1024;
	float m_PosTv_Size = (float)  120 / 1024;
	float m_Add_Tv_Size = (float) 120 / 1024;
};

class BeamVerticality
{
public:
	bool BeamVerticalityeFlag = false;
	float m_PosX;
	float m_PosY;
	float m_DrawSizeWidth = 120;
	float m_DrawSizeHight = 880;
	float m_PosTu      = (float)    0 / 1024;
	float m_PosTu_Size = (float)  120 / 1024;
	float m_Add_Tu_Size = (float)120 / 1024;
	float m_PosTv      = (float)    0 / 1024;
	float m_PosTv_Size = (float) 1024 / 1024;
};


#endif