#pragma once
#include"IClonable.h"
#include<windef.h>
namespace espoir{

struct ControlInfo;
class Form;


//スマートポインタをSPという名前を頭につけて宣言
SP_TDEF(Form);
SP_TDEF(ControlInfo);


//ウィンドウの状態を持つフォームクラス
class Form : public IClonable<Form>
{
private:
	//フォームの情報
	SPControlInfo info_;

	//現在生成されているフォームの数
	static unsigned int form_n_;
	
	//フォームのウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	Form(void);
	virtual ~Form(void);

	//フォーム情報の取得
	SPControlInfo GetInfo();

	//タイトルの設定
	void SetText(String text);

	//フォームを表示する
	void Show();

	//フォームのクローンを生成する
	Form* Clone();
};

}