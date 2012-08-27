#pragma once
#include"IClonable.h"
#include<windef.h>
#include"notify.h"
namespace espoir{

struct ControlInfo;
class Form;
//class Notify;

//Aboutダイアログ
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//ウィンドウの種類
enum WindowType{
	DirectX,
	DbgWnd
};

	//通知アイコン
	static Notify notify;


//スマートポインタをSPという名前を頭につけて宣言
SP_TDEF(Form);
SP_TDEF(ControlInfo);
SP_TDEF(Notify);

//ウィンドウの状態を持つフォームクラス
class Form
{
private:


	//static boost::shared_ptr<Notify> notify;

	//フォームの情報
	SPControlInfo info_;

	//現在生成されているフォームの数
	static unsigned int form_n_;
	

	//ゲームメイン画面のウィンドウプロシージャ
	static LRESULT CALLBACK DbgWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK DXWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

	//デバッグウィンドウ用のインスタンスハンドル
	static HINSTANCE dbgWndHInst_;

	//インスタンスハンドル
	static HINSTANCE hInst_;

	//ウィンドウの生成
	void CreateWnd();

	//タイトルの初期化
	void InitTitle();

	//フォーム情報の初期化
	void InitFormInfo();

	//ウィンドウクラスの登録
	void RgWndClass();

	//ウィンドウタイプ
	WindowType wt_;

public:
	Form(WindowType wt);
	virtual ~Form(void);

	//フォーム情報の取得
	SPControlInfo GetInfo();

	//タイトルの設定
	//void SetText(String text);

	//ウィンドウハンドルを取得
	HWND GetHandle();

	//フォームを表示する
	void Show();
};

}
