// espoir.cpp : アプリケーションのエントリ ポイントを定義します。
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
	OutputDebugString(_T("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n"));
	OutputDebugString(_T("☆☆☆☆☆☆☆☆☆☆　　S T A R T！　！　　　　　☆☆☆☆☆☆☆☆☆☆☆\n"));
	OutputDebugString(_T("☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\n"));
	OutputDebugString(_T("\n\n\n"));



	//警告抑制
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//メッセージ（未使用）
	MSG msg;

	//アクセラレータ（ショートカットキー）のテーブル（未使用）
	HACCEL hAccelTable;

	//警告抑制
	UNREFERENCED_PARAMETER(hAccelTable);
	UNREFERENCED_PARAMETER(msg);

	using namespace espoir;
	using namespace std;

	SP_TDEF(Form);
	SP_TDEF(DDevice);

	//プログラム終了直前、メモリリークチェック
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

	//DirectX初期化
	SPDDevice device( new DDevice() );
	device->Init();

	//DirectXのメインループ
	device->DMainLoop();
}
