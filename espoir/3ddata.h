#pragma once

struct 3DData{

	//�}�e���A���̐�
	DWORD numMaterials;

	//�}�e���A��
	std::vector<D3DMATERIAL9> meshMaterials;
	
	//�e�N�X�`��
	std::vector<LPDIRECT3DTEXTURE9> textures;
};