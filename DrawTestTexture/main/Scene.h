#ifndef SCENE_H_
#define SCENE_H_

#include "class.h"
/**
* @brief 現在のシーンIDを戻り値で取得する
* @return 現在のシーンID
*/
SceneId GetCurrentSceneId();

/**
* @brief 現在のステップを戻り値で取得する
* @return 現在のステップ
*/
SceneStep GetCurrentSceneStep();

/**
* @brief 次のステップへ移動させる
* @param (SceneStep next_step) 次のステップ
*/
void ChangeSceneStep(SceneStep next_step);

void UpdateScene(Pointa* point, MapChipData MapData, VariableNumber* var, Count* count);

void DrawScene(Pointa* point, MapChipData MapData, Count* count, VariableNumber* var);

#endif // !
