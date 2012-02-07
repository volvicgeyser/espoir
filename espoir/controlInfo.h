#pragma once

//GUIオブジェクトの情報が格納されている構造体

#include"color.h"
typedef Point Size;


namespace espoir{
	
struct ControlInfo
{

	//ControlInfoスマポ化
	SP_TDEF(ControlInfo);

	//コンストラクタ
	ControlInfo(void);


	//インスタンスハンドル
	HINSTANCE hInst;
	//オブジェクトのウィンドウハンドル
	HWND hWnd;

	//背景色
	Color backColor;

	//デフォルトのサイズ
	Size defaultSize;

	//デスクトップ上の配置
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