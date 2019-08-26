#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include"class.h"
#include"Engine.h"
#include"Device.h"
#include"GameScene.h"

void InptKeystate(Count* count, KeyState* keyState, Bullet bullet[5]);

void ChraMove(Count* count, KeyState* keyState, MainChar* mainChar);

void FrameCount(Count* count, KeyState* keyState);

void HitJudge(MainChar* mainChar);

void DrowBeam(Count* count, VariableNumber* var, int MapChipList[20][28], BeamSide* beamSide, BeamVerticality* beamVerticality);

void DrawMeteorite(Count* count, VariableNumber* var, int MapChipList[20][28], Meteorite meteorite[]);

void DrawMeteoriteTwo(Count* count, VariableNumber* var, int MapChipList[20][28], Meteorite meteorite[]);

void DrawEnemy(Count* count, VariableNumber* var, int MapChipList[20][28], Enemy_Green e_green[], Enemy_White e_white[]);

void EnemyMove(Count* count, VariableNumber* var, Enemy_Green e_green[], Enemy_White e_white[]);

void Shot(Bullet bullet[5], KeyState* keyState);

void ShotMove(KeyState* keyState, Bullet bullet[5], MainChar* mainChar);

void ShotHitJudge(Bullet bullet[5], KeyState* keyState, MainChar* mainChar);

#endif // !GAMESYSTEM_H
