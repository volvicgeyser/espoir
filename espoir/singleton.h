#pragma once

//�ÓI�ɐ���
template<class ObjType>
class DefaultSingletonCreation{
public:
	//Create�����o�֐����Ăяo���ꂽ���_�Ő��������
	static ObjType* Create(){
		static ObjType obj;
		return &obj;
	}
	
	//static�Ɋm�ۂ���̂ŉ������Ȃ�
	static void Destroy(ObjType*){
		std::cout << "Destroy" << std::endl;
	}
};

template<class ObjType>
class DefaultLifeTimePolicy{
public:
	//atexit�ɓo�^
	static void ScheduleCall(ObjType*, void(*f)(void)){
		atexit(f);
	}

	//�_���O�����O�|�C���^�Q�Ǝ��ɗ�O�𓊂���
	static void OnDeadReference()
	{
		throw std::runtime_error("Singleton�I�u�W�F�N�g�͈�x�j������Ă��܂�");
	}
};

template<
	class ObjType,
	template<class> class CreationPolicy = DefaultSingletonCreation,
	template<class> class LifeTimePolicy = DefaultLifeTimePolicy 
>
class Singleton{
public:
	static ObjType* object_;
    static ObjType* GetInst(){
        //static ObjType* object;
        if(!object_){

			//Singleton�I�u�W�F�N�g����x�j������Ă��邩�ǂ����`�F�b�N
			if(isDestroyed_){
				LifeTimePolicy<ObjType>::OnDeadReference();
				isDestroyed_ = false;
			}

			//CreationPolicy�ɂ��I�u�W�F�N�g�̐���
            object_ = CreationPolicy<ObjType>::Create();

			BOOST_ASSERT(object_);

			//������ݒ肷��
			LifeTimePolicy<ObjType>::ScheduleCall(object_, &DestroySingleton);

        }
        return object_; 
    }
	//Singleton�I�u�W�F�N�g�̔j��
	//CreationPolicy�̔j�������o�֐����Ăяo��
	static void DestroySingleton(){
		BOOST_ASSERT(object_);
		CreationPolicy<ObjType>::Destroy(object_);
		isDestroyed_ = true;
	}
private:
	static bool isDestroyed_;
};


//�I�u�W�F�N�g��0(NULL)�ŏ�����
template<
	class O,
	template<class> class C,
	template<class> class L
>O* Singleton<O, C, L>::object_ = 0;


//�j���t���O�̏�����
template<
	class O,
	template<class> class C,
	template<class> class L
>bool Singleton<O, C, L>::isDestroyed_= 0;


