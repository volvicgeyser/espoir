namespace espoir{



//�ÓI�|�����[�t�B�Y��
//���z�֐��ɂ��I�[�o�[�w�b�h����

//�f�U�C���p�^�[��
//Prototype�̃C���^�[�t�F�[�X
template <class ChildClass>
struct IClonable{

	//Clone�֐�
	IClonable* Clone(){
		static_cast<ChildClass*>(this)->Clone();
	}
};


}