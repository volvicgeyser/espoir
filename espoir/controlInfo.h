#pragma once

//GUIオブジェクトの情報が格納されている構造体

#include"color.h"
typedef Point Size;


namespace espoir{
	
struct ControlInfo
{
	//コンストラクタ
	ControlInfo(void);

	//オブジェクトのウィンドウハンドル
	HWND hWnd;

	//背景色
	Color backColor;

	//デフォルトのサイズ
	Size defaultSize;

	//デスクトップ上の配置
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