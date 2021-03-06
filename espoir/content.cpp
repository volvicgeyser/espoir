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

	//Contentに画像データを登録します
	void Content::RegisterTexture(const String& unique_name, const SPTexture& spTexture)
	{
		this->textureMap_[unique_name] = spTexture;
	}

	//Contentに画像データが登録しているかどうか
	bool Content::IsExistsTexture(const String& unique_name)
	{
		return this->textureMap_.find(unique_name) != this->textureMap_.end() ;
	}
	Content::~Content()
	{
	}
}

