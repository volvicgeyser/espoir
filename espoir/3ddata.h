#pragma once

struct 3DData{

	//マテリアルの数
	DWORD numMaterials;

	//マテリアル
	std::vector<D3DMATERIAL9> meshMaterials;
	
	//テクスチャ
	std::vector<LPDIRECT3DTEXTURE9> textures;
};