#pragma once

//Com用のスマートポインタクラス
//テンプレートSingletonクラスに合わすためのもの
namespace espoir{

template <class ObjType> 
class ComPtr{
public:
	typedef ObjType* ObjTypePtr;
	typedef ::_com_ptr_t<::_com_IIID< ObjType , &__uuidof( ObjType ) > > SPObjType;
	typedef ComPtr<ObjType> this_type;
	ComPtr(){}
	//SPObjType operator=(SPObjType spObj){
	//	return this->spObj_;
	//}
	bool operator==(const SPObjType spObj){
		return this->spObj_ == spObj;
	}
	//bool operator==(const int spObj){
	//	BOOST_ASSERT(spObj == 0);
	//	return this->spObj_ == NULL;
	//}
	bool operator!=(const SPObjType spObj){
		return this->spObj_ != this->spObj_;
	}
	template <class Y>
	ComPtr& operator=(const ComPtr<Y>& comPtr){
		//BOOST_ASSERT(comPtr.spObj_ != NULL);
		if(comPtr.spObj_ == NULL)
			throw std::runtime_error("NULLです");
		//throw std::runtime_error("未実装");
		return *this;
	};
	explicit ComPtr(const ObjTypePtr obj){
		if(obj)
			this->spObj_.Attach(obj);
	}

	//ComPtr(const ComPtr<ObjType>& comPtr);

	template <class Y>
	ComPtr(const ComPtr<Y>& comPtr){
		//if(comPtr.spObj_ != NULL)
		//	throw;
		//BOOST_ASSERT(comPtr.spObj_ != NULL);
		if(!this->spObj_)
			this->spObj_.Attach(comPtr.spObj_);
	}
	template <class Y>
	void Attach(const ComPtr<Y>& objPtr){
		this->spObj_.Attach(objPtr);
	}
	SPObjType operator->(){
		if(!this->spObj_)
			throw std::runtime_error("ComPtrの中身がNULLです");
		return this->spObj_;
	}
	
	
	SPObjType& GetRef(){
		if(!this->spObj_)
			throw std::runtime_error("ComPtrの中身がNULLです");
		return this->spObj_;
	}
private:
	SPObjType spObj_;
	SPObjType& operator&(){}
};

}