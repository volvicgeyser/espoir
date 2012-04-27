#pragma once
#include"macro.h"

namespace espoir{

//�V���O���g���ŕێ�����I�u�W�F�N�g�̐������`����N���X
//new�������̂��X�}�[�g�|�C���^�ŕ�ݍ���ŕԂ�
template <class ObjType> 
class SPDefaultSingletonCreation{
SP_TDEF(ObjType)
public:
	static SPObjType Create(){
		return SPObjType(new ObjType);
	}
};

//�ÓI�ɐ���
template <class ObjType>
class SPSingletonStaticCreation{
SP_TDEF(ObjType)
public:
	static SPObjType Create(){
		static ObjType obj;
		return SPObjType(obj);
	}
};


//�e���v���[�g��Singleton
template <
	class ObjType,
	template <class> class CreationPolicy = SPDefaultSingletonCreation,
	template <class> class SmartPtr = boost::shared_ptr
		>
class SPSingleton : boost::noncopyable{
//SP_TDEF(ObjType)
typedef SmartPtr<ObjType> SPObjType;
public:

	//typedef SPObjType CreationPolicy<ObjType>::SPObjType;
	//static SPObjType operator->() {return getInst();}

	static SPObjType GetInst(){
		//�����^�Ȃ��x��������
		static SPObjType object_;
		if(object_ == NULL){
			//const SPObjType tmp(CreationPolicy<ObjType>::Create());	
			//if(tmp == NULL)
			//	throw std::runtime_error("�������I�u�W�F�N�g�������ł��Ă��܂���");
			object_ = CreationPolicy<ObjType>::Create();
		}
		return object_;
	}
};









}
