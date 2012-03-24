// espoir.cpp : アプリケーションのエントリ ポイントを定義します。
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
#ifdef OLD_CODE
	#define COLOR_TESTING
	#define POINT_TESTING
#endif

TEST(xfile1, xifle1){
	using namespace espoir;
	XFile x(_T(""));
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	using namespace espoir;
	using namespace std;


	//コンソール
	//Console c;

	//googleテスト初期化
	int argc = 0;
	char** argv=0;
	::testing::InitGoogleTest(&argc, argv);

	//Start!!
	ShowStart();

	//警告抑制
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	SP_TDEF(Form);
	SP_TDEF(DDevice);

	//プログラム終了直前、メモリリークチェック
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

	//DirectX初期化
	SPDDevice device( new DDevice() );
	device->Init();

	//DirectXのメインループ
	device->DMainLoop();

	//system("pause");
	return RUN_ALL_TESTS();
}
