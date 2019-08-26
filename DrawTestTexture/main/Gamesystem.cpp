#include"class.h"
#include"Engine.h"
#include"Device.h"
#include"GameScene.h"
#include <random>
#include <iostream>

/*
Bullet bullet[5];
Meteorite meteorite[8];
Enemy_Green e_green[2];
Enemy_White e_white[2];
*/

// キーの入力情報設定
void InptKeystate(Count* count, KeyState *keyState, Bullet bullet[5])
{
	if (keyState->Move== 0)
	{
		count->Frame4 = 0;

		if (GetKeyStatus(DIK_S))
		{
			keyState->Move = 1;
		}
		else
			if (GetKeyStatus(DIK_W))
			{
				keyState->Move = 2;
			}
		if (GetKeyStatus(DIK_A))
		{
			keyState->Move = 3;
		}
		else
			if (GetKeyStatus(DIK_D))
			{
				keyState->Move = 4;
			}
	}

	if (keyState->Shot == 0)
	{
		if (GetKeyStatus(DIK_DOWN))
		{
			keyState->Shot = 1;
			bullet[0].ShotFlag = true;
		}
		else
			if (GetKeyStatus(DIK_UP))
			{
				keyState->Shot = 2;
				bullet[0].ShotFlag = true;
			}
		if (GetKeyStatus(DIK_LEFT))
		{
			keyState->Shot = 3;
			bullet[0].ShotFlag = true;
		}
		else
			if (GetKeyStatus(DIK_RIGHT))
			{
				keyState->Shot = 4;
				bullet[0].ShotFlag = true;
			}
	}
}

// 10フレーム経たないと動かない
void ChraMove(Count* count, KeyState *keyState,MainChar * mainChar)
{
	if (count->Frame4 < 10)
	{
		switch (keyState->Move)
		{
		case 0:
			break;
		case 1:
			mainChar->m_PosY = mainChar->m_PosY + 4;
			break;
		case 2:
			mainChar->m_PosY = mainChar->m_PosY - 4;
			break;
		case 3:
			mainChar->m_PosX = mainChar->m_PosX - 4;
			break;
		case 4:
			mainChar->m_PosX = mainChar->m_PosX + 4;
			break;
		}
	}
}

// 10フレームたったら再度キー入力できるようになる
void FrameCount(Count* count, KeyState* keyState)
{
	if (count->Frame4 > 10)
	{
		count->Frame4 = 0;
		keyState->Move = 0;
	}
}

// ゲーム画面の当たり判定
void HitJudge(MainChar* mainChar)
{
	if (mainChar->m_PosX < 80)
	{
		mainChar->m_PosX = mainChar->m_PosX + 4;
	}else
		if (mainChar->m_PosX > 1160)
		{
			mainChar->m_PosX = mainChar->m_PosX - 4;
		}else
			if (mainChar->m_PosY < 80)
			{
				mainChar->m_PosY = mainChar->m_PosY + 4;
			}
			else
				if (mainChar->m_PosY > 840)
				{
					mainChar->m_PosY = mainChar->m_PosY - 4;
				}
}

// ビーム(予兆)の描画設定
void DrowBeam(Count* count, VariableNumber* var,int MapChipList[20][28], BeamSide* beamSide,BeamVerticality*  beamVerticality)
{

	if (count->Frame3 == (60 * 8))
	{
		std::mt19937 mt{ std::random_device{}() };

		std::uniform_int_distribution<int> swich(1, 2);
		std::uniform_int_distribution<int> r_with(1, 25); // 1 28
		std::uniform_int_distribution<int> r_hight(1, 17); // 1 20

		var->temp = swich(mt);
		int with = r_with(mt);
		int hight = r_hight(mt);


		switch (var->temp)
		{
		case 0:
			break;
		case 1: // with

			for (int a = 0; a < 20; a++)
			{
				for (int c = 0; c < 3; c++)
				{
					MapChipList[a][with + c] = 2;

				}

			}

			beamSide->m_PosX = 80;
			beamSide->m_PosY = with * 40 + 80;
			count->Frame3 = 0;

			break;
		case 2: // hight

			for (int a = 0; a < 28; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					MapChipList[hight + b][a] = 2;
				}
			}
			beamVerticality->m_PosX = hight * 40 + 80;
			beamVerticality->m_PosY = 80;
			count->Frame3 = 0;

			break;
		}
		var->BeamState = 1;
		count->Frame2 = 0;

	}

	if (var->BeamState == 1)
	{
		if (count->Frame2 == (60 * 2))
		{

			for (int a = 0; a < 20; a++)
			{
				for (int b = 0; b < 28; b++)
				{
					if (MapChipList[a][b] == 2)
					{
						MapChipList[a][b] = 1;
					}
				}
				
				var->BeamState = 0;
			}
			count->Frame2 = 0;

			if (var->temp == 1)
			{
				beamSide->BeamSideFlag = true;
			}else
				if (var->temp == 2)
				{
					beamVerticality->BeamVerticalityeFlag = true;
				}

		}
		
		
	}

	if ((beamVerticality->BeamVerticalityeFlag == true) || (beamSide->BeamSideFlag == true))
	{
		if (count->Frame2 % 12 == 0 || count->Frame2 < 60)
		{
			beamVerticality->m_PosTu     = beamVerticality->m_PosTu       + beamVerticality->m_Add_Tu_Size;
			beamVerticality->m_PosTu_Size = beamVerticality->m_PosTu_Size + beamVerticality->m_Add_Tu_Size;

			beamSide->m_PosTv      = beamSide->m_PosTv     + beamSide->m_Add_Tv_Size;
			beamSide->m_PosTv_Size = beamSide->m_PosTv_Size + beamSide->m_Add_Tv_Size;

		}

		if (count->Frame2 % 12 == 0 || (count->Frame2 > 60 && count->Frame2 < 120))
		{
			beamSide->m_PosTv      = beamSide->m_PosTv      - beamSide->m_Add_Tv_Size;
			beamSide->m_PosTv_Size = beamSide->m_PosTv_Size - beamSide->m_Add_Tv_Size;
		}
	}

}

void DrawMeteorite(Count* count, VariableNumber* var,int MapChipList[20][28], Meteorite meteorite[])
{
	// if(GetKeyStatus(DIK_M))
	if (count->Frame == (60 * 12))
	{
		std::mt19937 mt{ std::random_device{}() };

		// 右上
		std::uniform_int_distribution<int> LeftUp_With(0, 13);
		std::uniform_int_distribution<int> LeftUp_Hight(0, 9);

		int a =  LeftUp_With(mt);
		int b = LeftUp_Hight(mt);

		// MapChipList[LeftUp_Hight(mt)][LeftUp_With(mt)] = 3;
		MapChipList[b][a] = 3;
		meteorite[0].m_PosX = (a) * 40 + 80;
		meteorite[0].m_PosY = (b) * 40 + 80;
		// 左上	
		std::uniform_int_distribution<int> RightUp_With(14, 27);
		std::uniform_int_distribution<int> RightUp_Hight(0, 9);

		int c = RightUp_With(mt);
		int d = RightUp_Hight(mt);

		// MapChipList[RightUp_With(mt)][RightUp_Hight(mt)] = 3;
		MapChipList[d][c] = 3;
		meteorite[1].m_PosX = (c) * 40 + 80;
		meteorite[1].m_PosY = (d) * 40 + 80;
		// 右下
		std::uniform_int_distribution<int> LeftDown_With(0, 13);
		std::uniform_int_distribution<int> LeftDown_Hight(10, 19);

		int e = LeftDown_With(mt);
		int f = LeftDown_Hight(mt);

		// MapChipList[LeftDown_With(mt)][LeftDown_Hight(mt)] = 3;
		MapChipList[f][e] = 3;
		meteorite[2].m_PosX = (e) * 40 + 80;
		meteorite[2].m_PosY = (f) * 40 + 80;
		// 左下
		std::uniform_int_distribution<int> RightDown_With(14, 27);
		std::uniform_int_distribution<int> RightDown_Hight(10, 19);

		int g = RightDown_With(mt);
		int h = RightDown_Hight(mt);

		// MapChipList[RightDown_With(mt)][RightDown_Hight(mt)] = 3;
		MapChipList[h][g] = 3;
		meteorite[3].m_PosX = (g) * 40 + 80;
		meteorite[3].m_PosY = (h) * 40 + 80;

		var->MeteoriteDrawState = 0;
		var->MeteoriteState = 1;
		count->Frame5 = 0;
		count->Frame8 = 0;
	}

	if (var->MeteoriteState == 1)
	{
		if (count->Frame5 == (60 * 2))
		{

			for (int a = 0; a < 20; a++)
			{
				for (int b = 0; b < 28; b++)
				{
					if (MapChipList[a][b] == 3)
					{
						MapChipList[a][b] = 1;
					}
				}
				var->MeteoriteState = 0;
				var->MeteoriteDrawState = 1;
			}
		}
	}
}

void DrawMeteoriteTwo(Count* count, VariableNumber* var, int MapChipList[20][28], Meteorite meteorite[])
{
	// 
	// if(GetKeyStatus(DIK_M))
	if (count->Frame8 == (60 * 12))
	{
		std::mt19937 mt{ std::random_device{}() };

		// 右上
		std::uniform_int_distribution<int> LeftUp_With(0, 13);
		std::uniform_int_distribution<int> LeftUp_Hight(0, 9);

		int LeftUpWith = LeftUp_With(mt);
		int LeftUpHight = LeftUp_Hight(mt);

		// MapChipList[LeftUp_Hight(mt)][LeftUp_With(mt)] = 3;
		MapChipList[LeftUpHight][LeftUpWith] = 3;
		meteorite[4].m_PosX = (LeftUpWith) * 40 + 80;
		meteorite[4].m_PosY = (LeftUpHight) * 40 + 80;
		// 左上	
		std::uniform_int_distribution<int> RightUp_With(14, 27);
		std::uniform_int_distribution<int> RightUp_Hight(0, 9);

		int c = RightUp_With(mt);
		int d = RightUp_Hight(mt);

		// MapChipList[RightUp_With(mt)][RightUp_Hight(mt)] = 3;
		MapChipList[d][c] = 3;
		meteorite[5].m_PosX = (c) * 40 + 80;
		meteorite[5].m_PosY = (d) * 40 + 80;
		// 右下
		std::uniform_int_distribution<int> LeftDown_With(0, 13);
		std::uniform_int_distribution<int> LeftDown_Hight(10, 19);

		int e = LeftDown_With(mt);
		int f = LeftDown_Hight(mt);

		// MapChipList[LeftDown_With(mt)][LeftDown_Hight(mt)] = 3;
		MapChipList[f][e] = 3;
		meteorite[6].m_PosX = (e) * 40 + 80;
		meteorite[6].m_PosY = (f) * 40 + 80;
		// 左下
		std::uniform_int_distribution<int> RightDown_With(14, 27);
		std::uniform_int_distribution<int> RightDown_Hight(10, 19);

		int g = RightDown_With(mt);
		int h = RightDown_Hight(mt);

		// MapChipList[RightDown_With(mt)][RightDown_Hight(mt)] = 3;
		MapChipList[h][g] = 3;
		meteorite[7].m_PosX = (g) * 40 + 80;
		meteorite[7].m_PosY = (h) * 40 + 80;

		var->MeteoriteDrawState2 = 0;
		var->MeteoriteState = 1;
		count->Frame9 = 0;
		count->Frame = 0;
	}

	if (var->MeteoriteState == 1)
	{
		if (count->Frame9 == (60 * 2))
		{

			for (int a = 0; a < 20; a++)
			{
				for (int b = 0; b < 28; b++)
				{
					if (MapChipList[a][b] == 3)
					{
						MapChipList[a][b] = 1;
					}
				}
				var->MeteoriteState = 0;
				var->MeteoriteDrawState2 = 1;
			}
		}
	}
}

void DrawEnemy(Count* count, VariableNumber* var, int MapChipList[20][28], Enemy_Green e_green[],Enemy_White e_white[])
{
	
	std::mt19937 mt{ std::random_device{}() };

	if (count->Frame6 == (60 * 15))
	{

		std::uniform_int_distribution<int> a(1, 4);

		// 左壁
		std::uniform_int_distribution<int> LeftHight(0, 19);
		int left_height = LeftHight(mt);
		MapChipList[left_height][0] = 5;
		e_green[0].m_PosX = 80;
		e_green[0].m_PosY = (left_height) * 40 + 80;

		// 右壁
		std::uniform_int_distribution<int> RightHight(0, 19);
		int right_hight = RightHight(mt);
		MapChipList[right_hight][27] = 5;
		e_green[1].m_PosX = 1160;
		e_green[1].m_PosY = (right_hight) * 40 + 80;

		// 上壁
		std::uniform_int_distribution<int> UpWith(0, 27);
		int up_with = UpWith(mt);
		MapChipList[0][up_with] = 4;
		e_white[0].m_PosX = (up_with) * 40 + 80;
		e_white[0].m_PosY = 80;

		// 下壁
		std::uniform_int_distribution<int> DownWith(0, 27);
		int dorw_with = DownWith(mt);
		MapChipList[19][dorw_with] = 4;
		e_white[1].m_PosX = (dorw_with) * 40 + 80;
		e_white[1].m_PosY = 840;

		
		var->EnemyState = 1;
		count->Frame7 = 0;
		count->Frame6 = 0;

	}

	if (var->EnemyState == 1)
	{
		if (count->Frame7 == (60 * 2))
		{

			for (int a = 0; a < 20; a++)
			{
				for (int b = 0; b < 28; b++)
				{
					if (MapChipList[a][b] == 4)
					{
						MapChipList[a][b] = 1;
					}
					if (MapChipList[a][b] == 5)
					{
						MapChipList[a][b] = 1;
					}
				}
				var->EnemyState = 0;
			}
			var->EnemyDrawState = 1;
		}
	}
}

// 敵の動き
void EnemyMove(Count* count, VariableNumber* var, Enemy_Green e_green[], Enemy_White e_white[] )
{
	if (var->EnemyDrawState == 1)
	{
		e_green[0].m_PosX = e_green[0].m_PosX + 4;
		e_green[1].m_PosX = e_green[1].m_PosX - 4;
		e_white[0].m_PosY = e_white[0].m_PosY + 2;
		e_white[1].m_PosY = e_white[1].m_PosY - 2;
	}
	if (e_green[0].m_PosX == 1160)
	{
		e_green[0].m_PosX = 2000;
		e_green[1].m_PosY = 2000;
		e_green[0].m_PosX = 2000;
		e_green[1].m_PosY = 2000;

		
	}
	if(e_white[0].m_PosY == 840)
	{
		e_white[0].m_PosX = 2000;
		e_white[1].m_PosY = 2000;
		e_white[0].m_PosX = 2000; 
		e_white[1].m_PosY = 2000;

		var->EnemyDrawState = 0;
	}
}

// 玉の段数用
void Shot(Bullet bullet[5] , KeyState* keyState)
{
	switch (keyState->Shot)
	{
	case 0:
		break;
	case 1: // 一個目

		break;
	case 2: // 二個目

		break;
	case 3: // 三個目

		break;
	case 4: // 四個目

		break;
	case 5: // 五個目

		break;
	} 
}

void ShotMove(KeyState* keyState, Bullet bullet[5] , MainChar* mainChar)
{

	if (bullet[0].ShotFlag == false)
	{
		if (((int)mainChar->m_PosX % 40 == 0) && ((int)mainChar->m_PosY % 40 == 0))
		{
			bullet[0].m_PosX = mainChar->m_PosX;
			bullet[0].m_PosY = mainChar->m_PosY;
		}
		else
		{
			bullet[0].m_PosX = (int)((int)mainChar->m_PosX / 40) * 40;
			bullet[0].m_PosY = (int)((int)mainChar->m_PosY / 40) * 40;
		}
		
	}

	if(bullet[0].ShotFlag == true)
	{
		switch (keyState->Shot)
		{
		case 0:
			break;
		case 1:
			bullet[0].m_PosY = bullet[0].m_PosY + 5;
			break;
		case 2:
			bullet[0].m_PosY = bullet[0].m_PosY - 5;
			break;
		case 3:
			bullet[0].m_PosX = bullet[0].m_PosX - 5;
			break;
		case 4:
			bullet[0].m_PosX = bullet[0].m_PosX + 5;
			break;
		}
	}
}

void ShotHitJudge(Bullet bullet[5], KeyState* keyState,MainChar* mainChar )
{
	if (bullet[0].m_PosX < 80)
	{
		bullet[0].ShotFlag = false;
		keyState->Shot = 0;
		bullet[0].m_PosX = mainChar->m_PosX;
		bullet[0].m_PosY = mainChar->m_PosY;
	}
	else
		if (bullet->m_PosX > 1160)
		{
			bullet[0].ShotFlag = false;
			keyState->Shot = 0;
			bullet[0].m_PosX = mainChar->m_PosX;
			bullet[0].m_PosY = mainChar->m_PosY;
		}
		else
			if (bullet->m_PosY < 80)
			{
				bullet[0].ShotFlag = false;
				keyState->Shot = 0;
				bullet[0].m_PosX = mainChar->m_PosX;
				bullet[0].m_PosY = mainChar->m_PosY;
			}
			else
				if (bullet->m_PosY > 840)
				{
					bullet[0].ShotFlag = false;
					keyState->Shot = 0;
					bullet[0].m_PosX = mainChar->m_PosX;
					bullet[0].m_PosY = mainChar->m_PosY;
				}
}