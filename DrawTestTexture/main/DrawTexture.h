#ifndef DRAWTEXTURE
#define DRAWTEXTURE

//const int MAX_TEXTURE = 10;
//TEXTUREDATA texture[MAX_TEXTURE];

// #include <D3dx9tex.h>

#include "class.h"

#define MAP_SIZE_WIDTH (28)	
#define MAP_SIZE_HEIGHT (20)

void Draw(float x, float y, float width, float height, float tu, float tv, float tu_width, float tv_height, LPDIRECT3DTEXTURE9* Texture, DirectX directX);

void DrawEx(float x, float y, float width, float height, LPDIRECT3DTEXTURE9* Texture, DirectX directX);

void LoadTexture(const char* file_name, LPDIRECT3DTEXTURE9* Texture, int texture_number, DirectX* directX);

void DrawMapChip(DirectX* directX, MapChipData MapData, LPDIRECT3DTEXTURE9* Texture, int MapChipList[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH]);

void DrawMap(MapChipData MapData, DirectX* directX, LPDIRECT3DTEXTURE9* Texture);

void DrawTest(float x, float y, float width, float height, float tu, float tv, float tu_width, float tv_height, LPDIRECT3DTEXTURE9* Texture, DirectX directX);
#endif // !1