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

	//Content‚É‰æ‘œƒf[ƒ^‚ğ“o˜^‚µ‚Ü‚·
	void Content::RegisterTexture(const String& unique_name, const SPTexture& spTexture)
	{
		this->textureMap_[unique_name] = spTexture;
	}

	//Content‚É‰æ‘œƒf[ƒ^‚ª“o˜^‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©
	bool Content::IsExistsTexture(const String& unique_name)
	{
		return this->textureMap_.find(unique_name) != this->textureMap_.end() ;
	}
	Content::~Content()
	{
	}
}

