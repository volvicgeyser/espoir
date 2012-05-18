// espoir.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "main.h"
#include "DDevice.h"
#include "debug.h"
#include "color.h"
#include "Form.h"
#include "controlInfo.h"
#include "Console.h"
#include "xfile.h"
#include "singleton.h"
#include "cast.h"
#include "new.h"
#include "system.h"

#ifdef _DEBUG
	#include "Singleton_test.h"
	#include "gametime_test.h"
	#include "cast_test.h"
	#include "new_test.h"
#endif

#ifdef OLD_CODE
	#define COLOR_TESTING
	#define POINT_TESTING
#endif

//X�t�@�C���ǂݍ��݂̃e�X�g
//TEST(xfile1, Disable_xfile1){
//    using namespace espoir;
//    XFile::Load(_T(""));
//}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	using namespace espoir;
	using namespace std;


	//�Q�[���J�n���ォ��GameTime�̃R���X�g���N�^�Ăяo���ŏ���������
	sys::Time::GetInst();
	
	//�R���\�[��
	//Console c;

	//google�e�X�g������
	int argc = 0;
	char** argv=0;
	::testing::InitGoogleTest(&argc, argv);

	//Start!!
	ShowStart();

	//�x���}��
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	SP_TDEF(Form);
	//SP_TDEF(DDevice);

	//�v���O�����I�����O�A���������[�N�`�F�b�N
	CheckMemoryLeaks();


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
	SPSingleton<DDevice>::GetInst()->Init();

	//DirectX�̃��C�����[�v
	SPSingleton<DDevice>::GetInst()->DMainLoop();

	//system("pause");
	return RUN_ALL_TESTS();
}
