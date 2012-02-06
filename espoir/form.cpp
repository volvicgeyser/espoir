#include "StdAfx.h"
#include "Form.h"
#include "controlInfo.h"
#include "debug.h"

namespace espoir{

Form::Form(void)
{
	//this->hWnd_.reset(new HWND);]
	if(this->info_.get() != NULL){
		DOut() << "pointer is not null" << std::endl;
		throw std::runtime_error("point is not null");
	}
	//SPControlInfo info(new ControlInfo);
	this->info_.reset(new ControlInfo);
	this->info_->text = _T("Form");
	//クラス名とタイトル
	String title = this->info_->text;
	title.append(boost::lexical_cast<String>(form_n_));
	this->info_->text = title.c_str();

	//インスタンスの取得
	HINSTANCE hInst = GetModuleHandle(NULL);
	
	//ウィンドウクラスの登録
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= Form::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	//wcex.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_ESPOIR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ESPOIR);
	wcex.lpszClassName	= title.c_str();
	//wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	ATOM atom = RegisterClassEx(&wcex);

	//ウィンドウの生成
	this->info_->hWnd  = CreateWindow(  title.c_str() , title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);
	DOut dout;
	dout << GetLastError() << std::endl;
	this->form_n_++;
	
}

SPControlInfo Form::GetInfo(){
	return this->info_;
}
LRESULT CALLBACK Form::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){
		case WM_DESTROY:
			break;
		case WM_PAINT:
			break;
		case WM_CREATE:
			CreateWindow(  _T("EDIT") , _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE,
				100, 50, 200, 150, hWnd, (HMENU)1, ((LPCREATESTRUCT)(lParam))->hInstance, NULL);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

Form::~Form(void)
{
	
}

Form* Form::Clone(){
	return new Form();
};

void Form::Show(){
	if(this->info_->hWnd != NULL){
		//適当
		STARTUPINFO Info;
		GetStartupInfo(&Info);
		int nCmdShow = Info.wShowWindow;

		ShowWindow(this->info_->hWnd, nCmdShow);
		UpdateWindow(this->info_->hWnd);
	}
}
void Form::SetText(String text){
	this->info_->text = text;
	SetWindowText(this->info_->hWnd, text.c_str());
}

unsigned int Form::form_n_ = 0;

}