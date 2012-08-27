#pragma once
#include"IClonable.h"
#include<windef.h>
#include"notify.h"
namespace espoir{

struct ControlInfo;
class Form;
//class Notify;

//About�_�C�A���O
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//�E�B���h�E�̎��
enum WindowType{
	DirectX,
	DbgWnd
};

	//�ʒm�A�C�R��
	static Notify notify;


//�X�}�[�g�|�C���^��SP�Ƃ������O�𓪂ɂ��Đ錾
SP_TDEF(Form);
SP_TDEF(ControlInfo);
SP_TDEF(Notify);

//�E�B���h�E�̏�Ԃ����t�H�[���N���X
class Form
{
private:


	//static boost::shared_ptr<Notify> notify;

	//�t�H�[���̏��
	SPControlInfo info_;

	//���ݐ�������Ă���t�H�[���̐�
	static unsigned int form_n_;
	

	//�Q�[�����C����ʂ̃E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK DbgWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK DXWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

	//�f�o�b�O�E�B���h�E�p�̃C���X�^���X�n���h��
	static HINSTANCE dbgWndHInst_;

	//�C���X�^���X�n���h��
	static HINSTANCE hInst_;

	//�E�B���h�E�̐���
	void CreateWnd();

	//�^�C�g���̏�����
	void InitTitle();

	//�t�H�[�����̏�����
	void InitFormInfo();

	//�E�B���h�E�N���X�̓o�^
	void RgWndClass();

	//�E�B���h�E�^�C�v
	WindowType wt_;

public:
	Form(WindowType wt);
	virtual ~Form(void);

	//�t�H�[�����̎擾
	SPControlInfo GetInfo();

	//�^�C�g���̐ݒ�
	//void SetText(String text);

	//�E�B���h�E�n���h�����擾
	HWND GetHandle();

	//�t�H�[����\������
	void Show();
};

}
