#include <stdio.h>
#include <windows.h>
#include <d3d9.h>

#include "Engine.h"
#include "class.h"

#include "Scene.h"
#include "TitleScene.h"
#include "SetScene.h"
#include "Option.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Scene.h"


/*
Sceneの流れ
Title -> Set -> Option -> Set -> Game -> Result -> Set

*/

//Pointa point;

void FrameCount(Count* count);
static SceneId g_CurrentSceneId = SceneId::TitleScene;		// 動作中シーンID
static SceneStep g_CurrentSceneStep = SceneStep::InitStep;	// 動作中シーンのステップ

SceneId GetCurrentSceneId()
{
	return g_CurrentSceneId;
}

SceneStep GetCurrentSceneStep()
{
	return g_CurrentSceneStep;
}

void ChangeSceneStep(SceneStep next_step)
{
	g_CurrentSceneStep = next_step;
}

void UpdateScene(Pointa* point, MapChipData MapData, VariableNumber* var, Count* count)
{
	int current_scene_id = SceneId::TitleScene;


	while (true)
	{
		UpdateInput(point);
		SceneId result_id = g_CurrentSceneId;

		switch (g_CurrentSceneId)
		{
			// タイトルシーン
		case SceneId::TitleScene:
			result_id = TitleSceneMain(point, count);
			break;
			// 難易度設定シーン
		case SceneId::SetScene:
			result_id = SetSceneMain(point, count, var);
			break;
			// 設定、ヘルプシーン
		case SceneId::OptionScene:
			result_id = OptionSceneMain(point);
			break;
			// メインゲームシーン
		case SceneId::GameScene:
			result_id = GameSceneMain(point, var, count);
			break;
			// リザルトシーン
		case SceneId::ResultScene:
			result_id = ResultSceneMain(point,count);
			break;

		}

		DrawScene(point, MapData, count, var);

		FrameCount(count);

		if (result_id != g_CurrentSceneId)
		{
			g_CurrentSceneId = result_id;
			ChangeSceneStep(SceneStep::InitStep);
		}
	}
}

void DrawScene(Pointa* point, MapChipData MapData, Count* count, VariableNumber* var)
{
	if (DrawStart(point) == false)
	{
		return;
	}
	if (g_CurrentSceneStep == SceneStep::MainStep)
	{
		switch (g_CurrentSceneId)
		{
		case SceneId::TitleScene:
			DrawTitleScene(point, count);
			break;
		case SceneId::SetScene:
			DrawSetScene(point, count, var);
			break;
		case SceneId::OptionScene:
			DrawOptionScene(point);
			break;
		case SceneId::GameScene:
			DrawGameScene(point, MapData,var);
			break;
		case SceneId::ResultScene:
			DrawResultScene(point, count);
			break;
		}
	}


	point->pDevice->EndScene();
	point->pDevice->Present(NULL, NULL, NULL, NULL);
}

void FrameCount(Count* count)
{
	count->Frame = count->Frame + 1;
	count->Frame2 = count->Frame2 + 1;
	count->Frame3 = count->Frame3 + 1;
	count->Frame4 = count->Frame4 + 1;
	count->Frame5 = count->Frame5 + 1;
	count->Frame6 = count->Frame6 + 1;
	count->Frame7 = count->Frame7 + 1;
	count->Frame8 = count->Frame8 + 1;
	count->Frame9 = count->Frame9 + 1;
	count->Frame10 = count->Frame10 + 1;
	count->StarDrawCount = count->StarDrawCount + 1;
}
