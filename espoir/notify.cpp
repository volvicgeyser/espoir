#include"stdafx.h"
#include"notify.h"
#include"system.h"
#include"debug.h"

namespace espoir{
	Notify::Notify(){
		//BOOST_ASSERT(!msg.empty());

		//バルーンとタスクトレイの設定
		//ZeroMemory(&notifyData, sizeof(NOTIFYICONDATA));
		notifyData = boost::shared_ptr<NOTIFYICONDATA>(new NOTIFYICONDATA(), NotifyDeleter() );
		notifyData->cbSize = sizeof(NOTIFYICONDATA);
		notifyData->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
		notifyData->uID = 0;
		notifyData->uCallbackMessage = WM_MYNOTIFY;
		notifyData->uTimeout = 1000;
		notifyData->hWnd = sys::Form::GetInst()->GetHandle();
		notifyData->hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);

		if(!notifyData->hWnd){
			throw std::runtime_error("ウィンドウハンドルがnullです");
		}
		_tcscpy_s(notifyData->szInfoTitle, _T("espoirが起動しました"));
		Stringstream str;
		str << _T("ここにデバッグメッセージやゲームの情報が表示されます") << std::endl;
		str << _T("ゲームが初期化されました") << std::endl;
		str << _T("■キャラクターが作成されました") << std::endl;
		str << _T("x = 100 y = 200");
		_tcscpy_s(notifyData->szInfo, str.str().c_str());
		_tcscpy_s(notifyData->szTip, _T("test"));

		if(!Shell_NotifyIcon(NIM_ADD, notifyData.get())){
			//throw std::runtime_error("通知に失敗しました");
		}
		DOut dout;
		dout << GetLastError() << std::endl;

	}
	void Notify::sendMessage(const String& msg){
		//_tcscpy_s(notifyData.szTip, msg.c_str());

		//ZeroMemory(&notifyData, sizeof(NOTIFYICONDATA));
		notifyData->uFlags =  NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
		notifyData->dwInfoFlags = 0;
		notifyData->hWnd = sys::Form::GetInst()->GetHandle();
		notifyData->cbSize = sizeof(NOTIFYICONDATA);
		notifyData->uTimeout = 10000;
		_tcscpy_s(notifyData->szInfoTitle, _T("espoir通知"));
		_tcscpy_s(notifyData->szInfo, msg.c_str());

		if(!Shell_NotifyIcon(NIM_MODIFY, notifyData.get()))
			throw std::runtime_error("通知失敗");

		//DOut dout;
		//dout << GetLastError() << std::endl;
	}
}

TEST(shellnotifyTest, notify){
	using namespace espoir;
	//notify( String(_T("abc")) );
}