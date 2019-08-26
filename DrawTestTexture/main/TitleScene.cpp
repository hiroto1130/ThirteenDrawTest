#include<stdio.h>
#include"Scene.h"
#include"class.h"
#include"DrawTexture.h"
#include"Device.h"

void DrawTitleScene(Pointa* point, Count* count);
void InitTitleScene(Pointa* point, Count* count);
void UpdateTitleScene(Pointa* n);
SceneId FinisTitleScene();

TEXTUREDATA TitleTextureData;



SceneId TitleSceneMain(Pointa* point, Count* count)
{
	switch (GetCurrentSceneStep())
	{
		// 初期化
	case SceneStep::InitStep:
		InitTitleScene(point, count);
		break;
		// 本編
	case SceneStep::MainStep:

		UpdateTitleScene(point);
		break;
		// 終了
	case SceneStep::EndStep:
		return FinisTitleScene();
		break;
	}

	return SceneId::TitleScene;
}

void DrawTitleScene(Pointa* point, Count* count)
{
	DrawEx(0, 0, 1280, 960, &TitleTextureData.m_pTexture[TitleTextureList::MainTitleTexture], *point);
	DrawTest(48, 130, 730, 730, 0, 0, 1, 1, &TitleTextureData.m_pTexture[TitleTextureList::RogTexture], *point);
}

// 描画設定等
void InitTitleScene(Pointa* point, Count* count)
{

	LoadTexture("Texture/Title.png", &TitleTextureData.m_pTexture[TitleTextureList::MainTitleTexture], 0, point);
	LoadTexture("Texture/image.png", &TitleTextureData.m_pTexture[TitleTextureList::RogTexture], 0, point);

	count->Frame = 0;

	ChangeSceneStep(SceneStep::MainStep);

}

// 次のシーンに行くための条件記入
void UpdateTitleScene(Pointa* n)
{
	
	if (GetKeyStatus(DIK_RETURN))
	{

		ChangeSceneStep(SceneStep::EndStep);
	}
}

// 次に飛ぶシーン先の設定
SceneId FinisTitleScene()
{
	for (int a = 0; a < TitleTextureList::MaxTitleTexture; a++)
	{


		TitleTextureData.m_pTexture[a]->Release();
		TitleTextureData.m_pTexture[a] = nullptr;
	}

	// 次のシーンの遷移先IDを返す
	return SceneId::SetScene;
}

