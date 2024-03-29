﻿#include"class.h"
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

			if (count->BulletCount < 4)
			{
				count->BulletCount = count->BulletCount + 1;
			}

		}
		else
			if (GetKeyStatus(DIK_UP))
			{
				keyState->Shot = 2;
				bullet[0].ShotFlag = true;

				if (count->BulletCount < 4)
				{
					count->BulletCount = count->BulletCount + 1;
				}
			}
		if (GetKeyStatus(DIK_LEFT))
		{
			keyState->Shot = 3;
			bullet[0].ShotFlag = true;

			if (count->BulletCount < 4)
			{
				count->BulletCount = count->BulletCount + 1;
			}
		}
		else
			if (GetKeyStatus(DIK_RIGHT))
			{
				keyState->Shot = 4;
				bullet[0].ShotFlag = true;

				if (count->BulletCount < 4)
				{
					count->BulletCount = count->BulletCount + 1;
				}
			}
	}

	if (GetKeyStatus(DIK_R))
	{
		bullet->BulletCount = 0;
	}

}


void MainChar::InputTv(int Tu, int Tu_Size)
{

	m_PosTu = (float) Tu / 1024;
	m_PosTu_Size =(float) Tu_Size / 1024;

}

// 10フレーム経たないと動かない(合計10フレーム,1フレーム X座標 +- 4 )

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

// 自キャラのモーション
void CharTextureChange(Count* count, MainChar* mainChar,Bullet * bullet)
{
	mainChar->Add_TvSize = 160 * count->BulletCount;

	if (count->Frame10 == 10)
	{
		mainChar->InputTv(80 + mainChar->Add_TvSize, 120 + mainChar->Add_TvSize);
	}
	else
		if (count->Frame10 == 20)
		{
			mainChar->InputTv(120 + mainChar->Add_TvSize, 160 + mainChar->Add_TvSize);
		}
		else
			if (count->Frame10 == 30)
			{
				mainChar->InputTv(160 + mainChar->Add_TvSize, 200 + mainChar->Add_TvSize);
			}
			else
				if (count->Frame10 == 40)
				{
					mainChar->InputTv(120 + mainChar->Add_TvSize, 160 + mainChar->Add_TvSize);
				}
				else
					if (count->Frame10 == 50)
					{
						mainChar->InputTv(80 + mainChar->Add_TvSize, 120 + mainChar->Add_TvSize);
					}
					else
						if (count->Frame10 == 60)
						{
							mainChar->InputTv(40 + mainChar->Add_TvSize, 80 + mainChar->Add_TvSize);
						}

	if (count->Frame10 > 60)
	{
		count->Frame10 = 0;
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

// ビーム描画位置入力関数(横)
void BeamSide::InputSidePosTv(float Tv, float TvSize)
{
	m_PosTv = Tv / 1024;
	m_PosTv_Size = TvSize / 1024;
}

// ビーム描画位置入力関数(縦)
void BeamVerticality::InputVerticalityPosTv(float Tv, float TvSize)
{
	m_PosTu = Tv / 1024;
	m_PosTu_Size = TvSize / 1024;
}

// ビーム描画(複数)
void SetBeams(Count* count, VariableNumber* var, int MapChipList[20][28], BeamSide* beamSide, BeamVerticality* beamVerticality, int WithDarwNumber, int HeightDrawNumber)
{
	std::mt19937 mt{ std::random_device{}() };

	for (int WithDrawCount = 0; WithDrawCount < WithDarwNumber; WithDrawCount++)
	{
		std::uniform_int_distribution<int> r_with(1, 25); // 1 28
		int with = r_with(mt);

		for (int a = 0; a < 20; a++)
		{
			for (int c = 0; c < 3; c++)
			{
				MapChipList[a][with + c] = 2;

			}

		}
		beamVerticality->m_PosX = with * 40 + 80;

	}

	for (int HeightDrawCount = 0; HeightDrawCount < HeightDrawNumber; HeightDrawCount++)
	{
		std::uniform_int_distribution<int> r_hight(1, 17); // 1 20
		int hight = r_hight(mt);

		for (int a = 0; a < 28; a++)
		{
			for (int b = 0; b < 3; b++)
			{
				MapChipList[hight + b][a] = 2;
			}
		}

		beamSide->m_PosY = hight * 40 + 80;

		break;
	}
	
}

// ビーム(予兆)の描画設定(一本の時のみ)
void SetBeam_first(Count* count, VariableNumber* var, int MapChipList[20][28], BeamSide* beamSide, BeamVerticality* beamVerticality, int BeamNnmber)
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
			beamVerticality->m_PosX = with * 40 + 80;
			break;

		case 2: // hight

			for (int a = 0; a < 28; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					MapChipList[hight + b][a] = 2;
				}
			}
			beamSide->m_PosY = hight * 40 + 80;

			break;
		}
		var->BeamState = 1;
		count->Frame2 = 0;
		count->Frame3 = 0;

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
			}
		}
	}

	/////////////////////////////////////////////////////////////////////// 描画関連 /////////////////////////////////////////////////////////////////

	
	if (count->Frame2 == 120)
	{
		if (var->temp == 1)
		{
			beamVerticality->BeamVerticalityeFlag = true;
		}
		else
			if (var->temp == 2)
			{
				beamSide->BeamSideFlag = true;

			}
	}

	if ((beamVerticality->BeamVerticalityeFlag == true) || (beamSide->BeamSideFlag == true))
	{
		if (count->Frame2 % 12 == 0)
		{
			if (count->Frame2 == 126)// 二個目
			{
				beamSide->InputSidePosTv(240,360);
				beamVerticality->InputVerticalityPosTv(240, 360);

			}else
				if (count->Frame2 == 132)// 三個目
				{
					beamSide->InputSidePosTv(360, 480);
					beamVerticality->InputVerticalityPosTv(360, 480);
				}else
					if (count->Frame2 == 138) // 四個目
					{
						beamSide->InputSidePosTv(480, 600);
						beamVerticality->InputVerticalityPosTv(480, 600);
					}else
						if (count->Frame2 == 144)// 五個目
						{
							beamSide->InputSidePosTv(600, 720);
							beamVerticality->InputVerticalityPosTv(600, 720);
						}else
							if (count->Frame2 == 216)// 六個目
							{
								beamSide->InputSidePosTv(480, 600);
								beamVerticality->InputVerticalityPosTv(480, 600);
							}else
								if (count->Frame2 == 222)// 七個目
								{
									beamSide->InputSidePosTv(360, 480);
									beamVerticality->InputVerticalityPosTv(360, 480);
								}else
									if (count->Frame2 == 228)// 八個目
									{
										beamSide->InputSidePosTv(240,360);
										beamVerticality->InputVerticalityPosTv(240, 360);
									}else
										if (count->Frame2 == 234)// 九個目
										{
											beamSide->InputSidePosTv(120, 240);
											beamVerticality->InputVerticalityPosTv(120, 240);
										}else
											if (count->Frame2 == 228)// 十個目
											{
												beamSide->InputSidePosTv(  0, 120);
												beamVerticality->InputVerticalityPosTv(  0, 120);
											}
		}
	}

	if (count->Frame2 == 240)
	{
		var->BeamState = 0;
		beamSide->BeamSideFlag = false;
		beamVerticality->BeamVerticalityeFlag = false;
	}
	

}

// ビームの描画処理
void DrawBeam()
{



}

// 隕石の描画(一段階目)
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

// 隕石の描画(二段階目)
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

void HitCharMeteorite(Meteorite meteorite[], MainChar* mainChar, Count* count, KeyState* keyState)
{
	for (int a = 0; a < 8; a++)
	{
		if (((mainChar->m_PosX + 40 > meteorite[a].m_PosX /*自キャラの右のあたり判定*/) && (mainChar->m_PosX < meteorite[a].m_PosX + 40)/*自キャラの左のあたり判定*/))
		{
			if ((mainChar->m_PosY < meteorite[a].m_PosY + 40)/*自キャラが下から当たった時ののあたり判定*/ && (mainChar->m_PosY + 40 > meteorite[a].m_PosY/*自キャラが上から当たった時のあたり判定*/))
			{

				switch (keyState->Move)
				{
				case 0:
					break;
				case 1:
					// down
					mainChar->m_PosY = mainChar->m_PosY - 4;
					break;
				case 2:
					// up
					mainChar->m_PosY = mainChar->m_PosY + 4;
					break;
				case 3:
					// lkeft
					mainChar->m_PosX = mainChar->m_PosX + 4;
					break;
				case 4:
					// right
					mainChar->m_PosX = mainChar->m_PosX - 4;
					break;
				}

			}
		}
	}
}

// 敵の描画
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
		e_green[0].DrawFlag = 1;

		// 右壁
		std::uniform_int_distribution<int> RightHight(0, 19);
		int right_hight = RightHight(mt);
		MapChipList[right_hight][27] = 5;
		e_green[1].m_PosX = 1160;
		e_green[1].m_PosY = (right_hight) * 40 + 80;
		e_green[1].DrawFlag = 1;

		// 上壁
		std::uniform_int_distribution<int> UpWith(0, 27);
		int up_with = UpWith(mt);
		MapChipList[0][up_with] = 4;
		e_white[0].m_PosX = (up_with) * 40 + 80;
		e_white[0].m_PosY = 80;
		e_white[0].DrawFlag = 1;

		// 下壁
		std::uniform_int_distribution<int> DownWith(0, 27);
		int dorw_with = DownWith(mt);
		MapChipList[19][dorw_with] = 4;
		e_white[1].m_PosX = (dorw_with) * 40 + 80;
		e_white[1].m_PosY = 840;
		e_white[1].DrawFlag = 1;

		
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
void EnemyMove(Count* count, VariableNumber* var, Enemy_Green e_green[], Enemy_White e_white[])
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
		e_green[0].m_PosX = 0;
		e_green[0].m_PosX = 0;
		e_green[0].DrawFlag = 2;

	}
	if (e_green[1].m_PosX == 80)
	{
		e_green[1].m_PosY = 0;
		e_green[1].m_PosY = 0;
		e_green[1].DrawFlag = 2;

	}
	if (e_white[0].m_PosY == 840)
	{
		e_white[0].m_PosX = 0;
		e_white[0].m_PosX = 0;
		e_white[0].DrawFlag = 2;

	}
	if (e_white[1].m_PosY == 80)
	{
		e_white[1].m_PosY = 0;
		e_white[1].m_PosY = 0;
		e_white[1].DrawFlag = 2;
	}
	if (e_white[0].DrawFlag == 2 && e_white[1].DrawFlag == 2)
	{
		if (e_green[0].DrawFlag == 2 && e_green[1].DrawFlag == 2)
		{
			var->EnemyDrawState = 0;

		}
	}
}

// 敵と弾丸のあたり判定
void HitBulletStar(Bullet* bullet, Count* count, Enemy_Green e_green[], Enemy_White e_white[], KeyState* keyState)
{

	for (int a = 0; a < 2; a++)
	{
		if (keyState->Shot > 0 && (e_green[a].DrawFlag == 1 || e_white[a].DrawFlag == 1) )
		{
			if ((bullet->m_PosX + 40 > e_green[a].m_PosX /*玉の右のあたり判定*/) && (bullet->m_PosX < e_green[a].m_PosX + 40)/*玉の左のあたり判定*/)
			{

				if ((bullet->m_PosY < e_green[a].m_PosY + 40)/*玉が下から当たった時ののあたり判定*/ && (bullet->m_PosY + 40 > e_green[a].m_PosY/*玉が上から当たった時のあたり判定*/))
				{
					e_green[a].DrawFlag = 2;

					e_green[a].m_PosX = 0;
					e_green[a].m_PosY = 0;

					if (count->BulletCount > 0 && count->BulletCount < 5)
					{
						count->BulletCount = 0;
					}
				}
			}

			if ((bullet->m_PosX + 40 > e_white[a].m_PosX /*玉の右のあたり判定*/) && (bullet->m_PosX < e_white[a].m_PosX + 40)/*玉の左のあたり判定*/)
			{

				if ((bullet->m_PosY < e_white[a].m_PosY + 40)/*玉が下から当たった時ののあたり判定*/ && (bullet->m_PosY + 40 > e_white[a].m_PosY/*玉が上から当たった時のあたり判定*/))
				{
					e_white[a].DrawFlag = 2;

					e_white[a].m_PosX = 0;
					e_white[a].m_PosY = 0;

					if (count->BulletCount > 0 && count->BulletCount < 5)
					{
						count->BulletCount = 0;
					}
				}
			}
		}
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

// 弾丸の移動描画
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

// 弾丸のあたり判定
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

// 星の描画
void StarDraw(Star star[12],Count* count)
{
	if (count->StarDrawCount == (5 * 60))
	{
		for(int a = 0; a < 4; a ++ )
		{
			if (star[a].DrawFlag == false)
			{
				std::mt19937 mt{ std::random_device{}() };

				std::uniform_int_distribution<int> With(0, 27);
				std::uniform_int_distribution<int> Height(0, 19);

				int with = With(mt);
				int height = Height(mt);

				star[a].m_PosX = with * 40 + 80;
				star[a].m_PosY = height * 40 + 80;

				star[a].DrawFlag = true;
			}
		
		}

		count->StarDrawCountReset();
	}


}

// 星と弾丸のあたり判定
void HitBulletStar(MainChar* mainChar, Star star[12], Count* count, KeyState* keyState)
{

	for (int a = 0; a < 12; a++)
	{

		if ((mainChar->m_PosX + 40 > star[a].m_PosX /*玉の右のあたり判定*/) && (mainChar->m_PosX < star[a].m_PosX + 40)/*玉の左のあたり判定*/)
		{

			if ((mainChar->m_PosY < star[a].m_PosY + 40)/*玉が下から当たった時ののあたり判定*/ && (mainChar->m_PosY + 40 > star[a].m_PosY/*玉が上から当たった時のあたり判定*/))
			{
				count->StarCount = count->StarCount + 1;
				star[a].DrawFlag = false;

				star[a].m_PosX = 0;
				star[a].m_PosY = 0;

				if (count->BulletCount > 0 && count->BulletCount < 5)
				{
					count->BulletCount = count->BulletCount - 1;
				}
			}
		}
	}
}

