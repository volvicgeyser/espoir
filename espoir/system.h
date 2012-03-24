#pragma once
#include"macro.h"

namespace espoir{

//�V���O���g���ŕێ�����I�u�W�F�N�g�̐������`����N���X
//new�������̂��X�}�[�g�|�C���^�ŕ�ݍ���ŕԂ�
template <class ObjType> 
class DefaultSingletonCreation{
	SP_TDEF(ObjType);
public:
	static SPObjType create(){
		return SPObjType(new ObjType);
	}
};


//�V���O���X���b�h
class SingletonSingleThread{};

//�e���v���[�g��Singleton
template <class ObjType, 
		 template <class> class CreationPolicy = DefaultSingletonCreation, 
		 class ThreadPolicy = SingletonSingleThread
		>
class Singleton{
SP_TDEF(ObjType)
public:
	
	//static SPObjType operator->() {return getInst();}
	static SPObjType getInst(){
		//�����^�Ȃ��x��������
		static SPObjType object_;
		if(object_.get() == NULL)
			object_ = CreationPolicy<ObjType>::create();	
		return object_;
	}
};

namespace system{

}

}
