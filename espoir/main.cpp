// espoir.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "main.h"
#include "DDevice.h"
#include "debug.h"
#include "color.h"
#include "Form.h"
#include "controlInfo.h"

#ifdef OLD_CODE
	#define COLOR_TESTING
	#define POINT_TESTING
#endif


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	OutputDebugString(_T("\n\n\n"));
	OutputDebugString(_T("��������������������������������������������������������������������\n"));
	OutputDebugString(_T("���������������������@�@S T A R T�I�@�I�@�@�@�@�@����������������������\n"));
	OutputDebugString(_T("��������������������������������������������������������������������\n"));
	OutputDebugString(_T("\n\n\n"));



	//�x���}��
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//���b�Z�[�W�i���g�p�j
	MSG msg;

	//�A�N�Z�����[�^�i�V���[�g�J�b�g�L�[�j�̃e�[�u���i���g�p�j
	HACCEL hAccelTable;

	//�x���}��
	UNREFERENCED_PARAMETER(hAccelTable);
	UNREFERENCED_PARAMETER(msg);

	using namespace espoir;
	using namespace std;

	SP_TDEF(Form);
	SP_TDEF(DDevice);

	//�v���O�����I�����O�A���������[�N�`�F�b�N
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

#ifdef USE_DX_DBG_WND
	SPForm f(new Form(DbgWnd));
	f->Show();
#endif


#ifdef POINT_TESTING
	Point p;
	DOut dout;
	p.x = 10;
	dout << p.x << endl;
#endif


#ifdef COLOR_TESTING
	espoir::Color c = espoir::White::Create();
	espoir::DOut dout;
	dout << c.r << std::endl;
#endif

	//DirectX������
	SPDDevice device( new DDevice() );
	device->Init();

	//DirectX�̃��C�����[�v
	device->DMainLoop();
}
