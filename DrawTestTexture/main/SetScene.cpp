#include<stdio.h>
#include"Scene.h"
#include"class.h"
#include"DrawTexture.h"
#include"Device.h"
#include"SetScene.h"

void DrawSetScene(Pointa* point, Count* count, VariableNumber* var);
void InitSetScene(Pointa* point);
void ResetSetScene(Count* count, VariableNumber* var);
void UpdateSetScene();
SceneId FinisSetScene();

VariableNumber var;
static bool KeyFlag = false;

TEXTUREDATA SetTextureData;

SceneId SetSceneMain(Pointa* point, Count* count, VariableNumber* var)
{
	switch (GetCurrentSceneStep())
	{
		// 初期化
	case SceneStep::InitStep:
		InitSetScene(point);
		break;
		// 本編
	case SceneStep::MainStep:
		UpdateSetScene();
		break;
		// 終了
	case SceneStep::EndStep:
		ResetSetScene(count, var);
		return FinisSetScene();
		break;
	}
	return SceneId::SetScene;
}

// 描画設定等
void DrawSetScene(Pointa* point, Count* count, VariableNumber* var)
{
	//DrawTest(1092, 816, 274, 86, size.normal_s_tu2, size.normal_s_tv, size.normal_e_tu2, size.normal_e_tv, &SetTextureData.m_pTexture[SetTextureList::levelselectTexture], *point);
	
}
void ResetSetScene(Count* count, VariableNumber* var)
{
};

void InitSetScene(Pointa* point)
{
	// LoadTexture("Texture/bg1.png", &SetTextureData.m_pTexture[SetTextureList::BackTexture], 0, point);

	ChangeSceneStep(SceneStep::MainStep);
}

// 次のシーンに行くための条件記入
void UpdateSetScene()
{
	if (GetKeyStatus(DIK_RETURN))
	{
		
	}

	ChangeSceneStep(SceneStep::EndStep);
}

// 次に飛ぶシーン先の設定
SceneId FinisSetScene()
{

	for (int a = 0; a < SetTextureList::MaxSetTexture; a++)
	{
		SetTextureData.m_pTexture[a]->Release();
		SetTextureData.m_pTexture[a] = nullptr;
	}

	return SceneId::GameScene;

}
