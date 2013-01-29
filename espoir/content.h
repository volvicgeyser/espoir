#pragma once
#include"intrusive_func.h"

//グラフィックを取り扱うクラス
namespace espoir
{

class Content
{
private:
	typedef boost::intrusive_ptr<IDirect3DTexture9> SPTexture;
	typedef std::map<String, SPTexture> TextureMap;
	TextureMap textureMap_;
public:
	Content::SPTexture GetTexture(const String&);
	void RegisterTexture(const String&, const SPTexture&);
	bool IsExistsTexture(const String&);
	Content();
	~Content();
};

}
