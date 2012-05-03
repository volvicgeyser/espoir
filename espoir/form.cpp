#include "StdAfx.h"
#include "Form.h"
#include "controlInfo.h"
#include "debug.h"
#include "Resource.h"
namespace espoir{

	HINSTANCE Form::hInst_ = GetModuleHandle(NULL);

void Form::InitTitle(){
	
	//�N���X���ƃ^�C�g��
	if(this->info_ == NULL){
		DOut dout;
		dout	<< "info is null"  << " at: "<<__LINE__ << std::endl;
	}
	//String title = _T("Form");

	//�t�H�[���̘A�Ԃ����Ԃ�����n�߂邩
	//const int start_at = 1;

	//title.append(boost::lexical_cast<String>(form_n_ + start_at));


	const String dxTitle = _T("espoir");
	const String dbgTitle = _T("debug window");
	//LoadString(Form::hInst_, IDS_APP_TITLE, dxTitle.c_str(), dxTitle.size());
	//LoadString(Form::hInst_, IDC_ESPOIR, dxTitle.c_str(), dxTitle.size());
	switch(this->wt_){
		case DirectX:
			this->info_->text = dxTitle;
			break;
		case DbgWnd:
			this->info_->text = dbgTitle;
			break;
	}

}
void Form::CreateWnd(){
	//�E�B���h�E�̐���
	this->info_->hWnd  = CreateWindow(  this->info_->text.c_str() , this->info_->text.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, this->info_->hInst, NULL);
	
	//�G���[������Ώo��
	DOut dout;
	if(GetLastError() != 0)
		dout << GetLastError() << "at: "<<__LINE__ << std::endl;

}

Form::~Form(){
}

void Form::InitFormInfo(){
	//�t�H�[�����̏�����
	if(this->info_ != NULL){
		throw std::runtime_error("�|�C���^��NULL�ł͂���܂���A���ɏ���������Ă���\��������܂�");
	}
	this->info_.reset(new ControlInfo);
	
	//�^�C�g���̏�����
	InitTitle();
	
	//this->info_->text = _T("Form");
}

void Form::RgWndClass(){
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style	 = CS_HREDRAW | CS_VREDRAW;

	//DirectX�̃E�B���h�E���f�o�b�O�E�B���h�E��
	switch(this->wt_){
		case DirectX:	
			wcex.lpfnWndProc = Form::DXWndProc;
			wcex.hIcon			= LoadIcon(this->info_->hInst, MAKEINTRESOURCE(IDI_ESPOIR));
			wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ESPOIR);
			wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
			break;
		case DbgWnd:
			wcex.lpfnWndProc =  Form::DbgWndProc;
			break;
	}
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= this->info_->hInst;
	//
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//
	wcex.lpszClassName	= this->info_->text.c_str();
	//

	ATOM atom = RegisterClassEx(&wcex);
}
Form::Form(WindowType wt)
{
	//�E�B���h�E�^�C�v�̐ݒ�
	this->wt_ = wt;

	//�t�H�[�����̏�����
	InitFormInfo();

	//�C���X�^���X�n���h���̎擾
	this->info_->hInst = GetModuleHandle(NULL);
	
	//�^�C�g���̏�����
	InitTitle();
	
	//�E�B���h�E�N���X�̓o�^
	RgWndClass();

	//	�E�B���h�E�̐���
	this->CreateWnd();

	//���݂̃E�B���h�E�̐��𑝂₷
	this->form_n_++;
	
}

//�t�H�[���̏����擾
SPControlInfo Form::GetInfo(){
	return this->info_;
}


//DirectX�̃��C���E�B���h�E
LRESULT CALLBACK Form::DXWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	int wmId;
	int wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch(msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: �`��R�[�h�������ɒǉ����Ă�������...
			EndPaint(hWnd, &ps);
			break;
		case WM_COMMAND:
			wmId   = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			
			// �I�����ꂽ���j���[�̉��:
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBox(Form::hInst_, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, msg, wParam, lParam);
			}
			break;
		case WM_CREATE:

			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}


//�f�o�b�O�E�B���h�E
LRESULT CALLBACK Form::DbgWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
		case WM_CREATE:
			CreateWindow(  _T("EDIT") , _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE,
				100, 50, 200, 150, hWnd, (HMENU)1, ((LPCREATESTRUCT)(lParam))->hInstance, NULL);
			break;
		case WM_CLOSE:
			//��\���ɂ��邾��
			ShowWindow(hWnd, SW_HIDE);

			//�E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W��n���Ȃ����ƂŃE�B���h�E��j�����Ȃ�
			return 0;
		case WM_DESTROY:
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}




//Form* Form::Clone(){
//	return new Form();
//};

void Form::Show(){
	if(this->info_->hWnd != NULL){
		//�v���O�����N�����ɂ��������ꂽ�E�B���h�E�̏�Ԃ��擾
		STARTUPINFO Info;
		GetStartupInfo(&Info);
		int nCmdShow = Info.wShowWindow;

		ShowWindow(this->info_->hWnd, nCmdShow);
		UpdateWindow(this->info_->hWnd);
	}
}
//void Form::SetText(String text){
//	this->info_->text = text;
//	SetWindowText(this->info_->hWnd, text.c_str());
//}

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���ł��B
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


HWND Form::GetHandle(){
	return this->info_->hWnd;
}


unsigned int Form::form_n_ = 0;

}
