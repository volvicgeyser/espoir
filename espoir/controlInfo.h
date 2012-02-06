#pragma once

//GUI�I�u�W�F�N�g�̏�񂪊i�[����Ă���\����

#include"color.h"
typedef Point Size;


namespace espoir{
	
struct ControlInfo
{
	//�R���X�g���N�^
	ControlInfo(void);

	//�I�u�W�F�N�g�̃E�B���h�E�n���h��
	HWND hWnd;

	//�w�i�F
	Color backColor;

	//�f�t�H���g�̃T�C�Y
	Size defaultSize;

	//�f�X�N�g�b�v��̔z�u
	//Point desktopLocation;

	std::vector<boost::shared_ptr<ControlInfo>> child;
	boost::shared_ptr<ControlInfo> parent;
	bool IsShowIcon;
	bool IsShowInTaskbar;
	Rect windowRect;
	String text;
	std::vector<boost::shared_ptr<ControlInfo>> controls;
	bool visible;
};

}