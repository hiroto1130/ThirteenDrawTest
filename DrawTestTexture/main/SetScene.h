#ifndef _SETSCENE_H_ 
#define _SETSCNEN_H_

SceneId SetSceneMain(DirectX* directX, Count* count, VariableNumber* var);

void DrawSetScene(DirectX* directX, Count* count, VariableNumber* var);

class TextureSize
{
public:
	/* 512 128
	result680.360
high565.560
score5.820 1024,329
level5.610 512 128
help0.510 274 86
easy0.445 322 61
Normal0.380 322 61
	*/
	//////////////////////////////////////////////////////////////
	float rog_s_tu = (float)5 / 2048;
	float rog_e_tu = (float)517 / 2048;
	float rog_s_tv = (float)610 / 1024;
	float rog_e_tv = (float)738 / 1024;
	//////////////////////////////////////////////////////////////
	float score_s_tu = (float)0 / 2048;
	float score_e_tu = (float)1024 / 2048;
	float score_s_tv = (float)10 / 1024;;
	float score_e_tv = (float)339 / 1024;
	//////////////////////////////////////////////////////////////
	float easy_s_tu = (float)0 / 2048;
	float easy_e_tu = (float)322 / 2048;
	float easy_s_tv = (float)445 / 1024;
	float easy_e_tv = (float)506 / 1024;
	float easy_s_tu2 = (float)322 / 2048;
	float easy_e_tu2 = (float)644 / 2048;
	/////////////////////////////////////////////////////////////
	float normal_s_tu = (float)0 / 2048;
	float normal_e_tu = (float)322 / 2048;
	float normal_s_tv = (float)380 / 1024;
	float normal_e_tv = (float)441 / 1024;
	float normal_s_tu2 = (float)322 / 2048;
	float normal_e_tu2 = (float)644 / 2048;
	////////////////////////////////////////////////////////////
	float help_s_tu = (float)0 / 2048;
	float help_e_tu = (float)274 / 2048;
	float help_s_tv = (float)510 / 1024;
	float help_e_tv = (float)596 / 1024;
	float help_s_tu2 = (float)274 / 2048;
	float help_e_tu2 = (float)548 / 2048;
};
#endif