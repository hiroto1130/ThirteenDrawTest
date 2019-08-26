#ifndef _RESULTSCENE_H_ 
#define _RESULTSCNEN_H_

SceneId ResultSceneMain(Pointa* point, Count* count);

void DrawResultScene(Pointa* point, Count* count);


class ResultTextureSize
{
public:
	int FlameCount = 0;
	float m_PosX = 0;
	float m_PosY = 0;
	float m_HightSize = 960;
	float m_WithSize = 1280;
	float m_Main_s_tu = 0;
	float m_Main_e_tu = 1;
	float m_Main_s_tv = 0;
	float m_Main_e_tv = 1;
};
#endif 