#pragma once
namespace espoir{
struct Font;

template<class ObjType>
struct DebugFontCreation{
	typedef boost::shared_ptr<ObjType> SPObjType;
	static SPObjType Create(){
		return boost::make_shared<ObjType>(_T("‚l‚r ƒSƒVƒbƒN"));
	}
};
}