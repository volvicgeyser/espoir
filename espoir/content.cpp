#include"stdafx.h"
#include "content.h"

namespace espoir{
	Content::Content()
	{
	}

	Content::SPTexture Content::GetTexture(const String& unique_name)
	{
		return this->textureMap_[unique_name];
	}

	//Content�ɉ摜�f�[�^��o�^���܂�
	void Content::RegisterTexture(const String& unique_name, const SPTexture& spTexture)
	{
		this->textureMap_[unique_name] = spTexture;
	}

	//Content�ɉ摜�f�[�^���o�^���Ă��邩�ǂ���
	bool Content::IsExistsTexture(const String& unique_name)
	{
		return this->textureMap_.find(unique_name) != this->textureMap_.end() ;
	}
	Content::~Content()
	{
	}
}

