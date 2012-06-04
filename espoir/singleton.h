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

	//shared_ptr�ɔC����̂Ŕj���͉������Ȃ�
	static void Destroy(ObjType){}
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


//C++�̋K���ɏ]���������Ǘ�
//obj1, obj2, obj3 �Ɛ��������� obj3, obj2, obj1 �Ƃ��������ɉ�������
template<class ObjType>
class SPDefaultLifetime
{
	//����! ObjType�̓X�}�[�g�|�C���^
public:
	static void ScheduleCall(ObjType, void(*func)(void)){
		std::atexit(func);
	}

	//��x�폜���ČĂяo���Ɨ�O����������
	static void OnDeadReference(){
		throw std::runtime_error("Singleton�I�u�W�F�N�g����x�j������Ă��܂�");
	}
};

//�e���v���[�g��Singleton
template <
	class ObjType,
	template <class> class CreationPolicy = SPDefaultSingletonCreation,
	template <class> class SmartPtr = boost::shared_ptr,
	template <class> class LifeTimePolicy = SPDefaultLifetime
		>
class SPSingleton : boost::noncopyable{
//SP_TDEF(ObjType)
typedef SmartPtr<ObjType> SPObjType;
//typedef SPSingleton<CreationPolicy, SmartPtr, LifeTimePolicy> self_type;
public:
	static SPObjType GetInst(){
		//�����^�Ȃ��x��������
		static SPObjType object_;
		if(object_ == NULL){

			//��x�j������Ă��Ȃ����ǂ����`�F�b�N
			if(isDestroyed_){
				LifeTimePolicy<SPObjType>::OnDeadReference();
				isDestroyed_ = true;
			}

			//�I�u�W�F�N�g�̐���
			object_ = CreationPolicy<ObjType>::Create();

			//�����Ǘ��o�^
			LifeTimePolicy<SPObjType>::ScheduleCall(object_, DestroySingleton);
		}
		return object_;
	}
	static void DestroySingleton(){
		BOOST_ASSERT(!isDestroyed_);
		//CreationPolicy<ObjType>::Destroy(object_);
	}
private:
	static bool isDestroyed_;
};

//�j���t���O�̏�����
template<class O, 
	template<class> class C, 
	template<class> class S,
	template<class> class L
>bool SPSingleton<O, C, S, L>::isDestroyed_ = false;

//�I�u�W�F�N�g�̏�����
//template<class O,
//    template<class> class C,
//    template<class> class S,
//    template<class> class L
//>S<O> SPSingleton<O, C, S, L>::object_ = 0;

//Comptr��p
//template <
//    class ObjType,
//    template <class> class CreationPolicy,
//    template <class> class SmartPtr
//>
//class SPSingleton : boost::noncopyable{
//public:
//};

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
public:
	static void ScheduleCall(ObjType*, boost::function<void (void)> func){
	}
};

template<
	class ObjType,
	template<class> class CreationPolicy = DefaultSingletonCreation,
	template<class> class LifeTimePolicy = DefaultLifeTimePolicy 
>
class Singleton{
public:
	static ObjType* object;
    static ObjType* GetInst(){
        //static ObjType* object;
        if(!object){
            object = CreationPolicy<ObjType>::Create();
			BOOST_ASSERT(object);
			LifeTimePolicy<ObjType>::ScheduleCall(object, &DestroySingleton);
        }
        return object; 
    }
	static void DestroySingleton(){
		
	}

};

//�I�u�W�F�N�g��0(NULL)�ŏ�����
template<
	class O,
	template<class> class C,
	template<class> class L
>O* Singleton<O, C, L>::object = 0;







}
