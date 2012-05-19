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
//SP_TDEF(ObjType)
typedef SmartPtr<ObjType> SPObjType;
public:
	static SPObjType GetInst(){
		//�����^�Ȃ��x��������
		static SPObjType object_;
		if(object_ == NULL){
			object_ = CreationPolicy<ObjType>::Create();
		}
		return object_;
	}
};



//�ÓI�ɐ���
template<class ObjType>
class DefaultSingletonCreation{
public:
	static ObjType* Create(){
		static ObjType obj;
		return &obj;
	}
};

template<class ObjType>
class DefaultLifeTimePolicy{
};

template<
	class ObjType,
	template<class> class CreationPolicy = DefaultSingletonCreation,
	template<class> class LifeTimePolicy = DefaultLifeTimePolicy 
>
class Singleton{
public:
    static ObjType* GetInst(){
        static ObjType* object;
        if(!object){
            object = CreationPolicy<ObjType>::Create();
			BOOST_ASSERT(object);
        }
        return object; 
    }

};







}
