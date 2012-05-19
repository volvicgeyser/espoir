#pragma once

namespace espoir{

//�^�ϊ��������Ȃ�
//��if���̃I�[�o�[�w�b�h�𔺂����I�ȃ`�F�b�N
//typeid�������ł������^�ł��邱�Ƃ͕ۏ؂���Ȃ����Ƃɒ���
template<class To, class From>
inline To type_check(const From& f){
	if(typeid(From) != typeid(To))
		throw std::runtime_error("RistrictCastPolicy: �^�̕ϊ���������Ă��܂���");
	return f;
}

//static_cast��Z�����邾��
template<class To, class From>
inline To cast(const From& f){
 	return static_cast<To>(f);
}

}