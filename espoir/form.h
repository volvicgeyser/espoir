#pragma once
#include"IClonable.h"
#include<windef.h>
namespace espoir{

struct ControlInfo;
class Form;


//�X�}�[�g�|�C���^��SP�Ƃ������O�𓪂ɂ��Đ錾
SP_TDEF(Form);
SP_TDEF(ControlInfo);


//�E�B���h�E�̏�Ԃ����t�H�[���N���X
class Form : public IClonable<Form>
{
private:
	//�t�H�[���̏��
	SPControlInfo info_;

	//���ݐ�������Ă���t�H�[���̐�
	static unsigned int form_n_;
	
	//�t�H�[���̃E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	Form(void);
	virtual ~Form(void);

	//�t�H�[�����̎擾
	SPControlInfo GetInfo();

	//�^�C�g���̐ݒ�
	void SetText(String text);

	//�t�H�[����\������
	void Show();

	//�t�H�[���̃N���[���𐶐�����
	Form* Clone();
};

}