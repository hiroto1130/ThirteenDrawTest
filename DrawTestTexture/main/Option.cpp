#include<stdio.h>
#include"Scene.h"
#include"class.h"
#include"DrawTexture.h"
#include"Device.h"

void InitOptionScene(DirectX* directX);
void UpdateOptionScene();
SceneId FinisOptionScene();

TEXTUREDATA OptionTextureData;

SceneId OptionSceneMain(DirectX* directX)
{
	switch (GetCurrentSceneStep())
	{
		// 初期化
	case SceneStep::InitStep:
		InitOptionScene(directX);
		break;

		// 本編
	case SceneStep::MainStep:
		UpdateOptionScene();
		break;
		// 終了
	case SceneStep::EndStep:
		return FinisOptionScene();
		break;
	}
	return SceneId::OptionScene;
}

// 描画設定等
void DrawOptionScene(DirectX* directX)
{
	//DrawTest(1045, 643, 179, 179, 0.25, 0, 0.5, 1, &OptionTextureData.m_pTexture[OptionTextureList::SabOptionTexture], *point);
}

// テクスチャ読み込み
void InitOptionScene(DirectX* directX)
{
	//LoadTexture("Texture/OptionChar.png", &OptionTextureData.m_pTexture[OptionTextureList::SabOptionTexture], 0, point);

	ChangeSceneStep(SceneStep::MainStep);
}

// 次のシーンに行くための条件記入
void UpdateOptionScene()
{
	if (GetKeyStatus(DIK_RETURN))
	{
		ChangeSceneStep(SceneStep::EndStep);
	}

}

// 次に飛ぶシーン先の設定
SceneId FinisOptionScene()
{
	for (int a = 0; a < OptionTextureList::MaxOptionTexture; a++)
	{
		OptionTextureData.m_pTexture[a]->Release();
		OptionTextureData.m_pTexture[a] = nullptr;
	}
	// 次のシーンの遷移先IDを返す
	return SceneId::SetScene;
}

