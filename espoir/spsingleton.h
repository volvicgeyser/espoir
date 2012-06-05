#pragma once
#include"macro.h"
#include"new.h"

namespace espoir{

//�V���O���g���ŕێ�����I�u�W�F�N�g�̐������`����N���X
//new�������̂��X�}�[�g�|�C���^�ŕ�ݍ���ŕԂ�
template <class ObjType> 
class SPDefaultSingletonCreation{
SP_TDEF(ObjType)
public:
	//�I�u�W�F�N�g�̐����֐�
	static SPObjType Create(){
		return SPObjType(new_<ObjType>());
	}
};

//�ÓI�ɐ���
//template <class ObjType>
//class SPSingletonStaticCreation{
//SP_TDEF(ObjType)
//public:
//    static SPObjType Create(){
//        static ObjType obj;
//        return SPObjType(obj);
//    }
//};

//�e���v���[�g��Singleton
template <
	class ObjType,
	template <class> class CreationPolicy = SPDefaultSingletonCreation,
	template <class> class SmartPtr = boost::shared_ptr
		>
class SPSingleton : boost::noncopyable{
typedef SmartPtr<ObjType> SPObjType;
public:
	static SPObjType GetInst(){
		//�����^�Ȃ��x��������
		//static SPObjType object_;
		if(object_ == NULL){

			//�I�u�W�F�N�g�̐���
			object_ = CreationPolicy<ObjType>::Create();
		}
		return object_;
	}
private:
	static SPObjType object_;
};

//�I�u�W�F�N�g�̎���
template<class O,
    template<class> class C,
	template<class> class S
>S<O> SPSingleton<O, C, S>::object_;

}
