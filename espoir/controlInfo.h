#pragma once

//GUI�I�u�W�F�N�g�̏�񂪊i�[����Ă���\����

#include"color.h"
typedef Point Size;


namespace espoir{
	
struct ControlInfo
{

	//ControlInfo�X�}�|��
	SP_TDEF(ControlInfo);

	//�R���X�g���N�^
	ControlInfo(void);


	//�C���X�^���X�n���h��
	HINSTANCE hInst;
	//�I�u�W�F�N�g�̃E�B���h�E�n���h��
	HWND hWnd;

	//�w�i�F
	Color backColor;

	//�f�t�H���g�̃T�C�Y
	Size defaultSize;

	//�f�X�N�g�b�v��̔z�u
	//Point desktopLocation;

	std::vector<SPControlInfo> child;
	SPControlInfo parent;
	bool IsShowIcon;
	bool IsShowInTaskbar;
	Rect windowRect;
	String text;
	std::vector<SPControlInfo> controls;
	bool visible;
};

}