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
#include "singleton.h"
#include "cast.h"
#include "new.h"
#include "system.h"

#ifdef _DEBUG
//	#include "Singleton_test.h"
	#include "gametime_test.h"
	#include "cast_test.h"
	#include "font_test.h"
	#include "boost_format_test.h"
//	#include "new_test.h"
	//#include "device_getref_test.h"
#endif

#ifdef OLD_CODE
	#define COLOR_TESTING
	#define POINT_TESTING
#endif

//Xファイル読み込みのテスト
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

	//ゲーム開始直後からGameTimeのコンストラクタ呼び出しで初期化する
	sys::Time::GetInst();
	
	//コンソール
	//boost::shared_ptr<Console> c(new Console(), ConsoleDeleter());

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
	//SP_TDEF(DDevice);

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
	Singleton<DDevice>::GetInst()->Init();

	//DirectXのメインループ
	Singleton<DDevice>::GetInst()->DMainLoop();

	//解放してみる
//    DOut dout;
//    for(ULONG cnt = sys::Device::GetInst()->Release(); 0L < cnt; cnt = sys::Device::GetInst()->Release()){
//        dout << _T("警告　解放テスト") << std::endl;
//        dout << cnt << endl;
//    }

	//system("pause");
	return RUN_ALL_TESTS();
}
