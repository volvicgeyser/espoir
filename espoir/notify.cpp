#include"stdafx.h"
#include"notify.h"
#include"system.h"
#include"debug.h"

namespace espoir{
	Notify::Notify(){
		//BOOST_ASSERT(!msg.empty());

		//�o���[���ƃ^�X�N�g���C�̐ݒ�
		//ZeroMemory(&notifyData, sizeof(NOTIFYICONDATA));
		this->notifyData = boost::shared_ptr<NOTIFYICONDATA>(new NOTIFYICONDATA(), NotifyDeleter() );
		this->notifyData->cbSize = sizeof(NOTIFYICONDATA);
		this->notifyData->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
		this->notifyData->uID = 0;
		this->notifyData->uCallbackMessage = WM_MYNOTIFY;
		this->notifyData->uTimeout = 1000;
		this->notifyData->hWnd = sys::Form::GetInst()->GetHandle();
		this->notifyData->hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);

		if(!this->notifyData->hWnd){
			throw std::runtime_error("�E�B���h�E�n���h����null�ł�");
		}
		_tcscpy_s(notifyData->szInfoTitle, _T("espoir���N�����܂���"));
		Stringstream str;
		str << _T("�����Ƀf�o�b�O���b�Z�[�W��Q�[���̏�񂪕\������܂�") << std::endl;
		str << _T("�Q�[��������������܂���") << std::endl;
		str << _T("���L�����N�^�[���쐬����܂���") << std::endl;
		str << _T("x = 100 y = 200");
		_tcscpy_s(notifyData->szInfo, str.str().c_str());
		_tcscpy_s(notifyData->szTip, _T("test"));

		if(!Shell_NotifyIcon(NIM_ADD, notifyData.get())){
			//throw std::runtime_error("�ʒm�Ɏ��s���܂���");
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
		_tcscpy_s(notifyData->szInfoTitle, _T("espoir�ʒm"));
		_tcscpy_s(notifyData->szInfo, msg.c_str());

		if(!Shell_NotifyIcon(NIM_MODIFY, notifyData.get()))
			throw std::runtime_error("�ʒm���s");

		//DOut dout;
		//dout << GetLastError() << std::endl;
	}
}

TEST(shellnotifyTest, notify){
	using namespace espoir;
	//notify( String(_T("abc")) );
}
