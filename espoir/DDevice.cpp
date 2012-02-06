
#include"stdafx.h"
#include"DDevice.h"
#include"debug.h"
#include"Resource.h"
ComPtr<IDirect3D9>::type espoir::DDevice::mDirect3D;
//::_com_ptr_t<::_com_IIID<IDirect3D9, &__uuidof(IDirect3D9)>>  espoir::DDevice::mDirect3D;
ComPtr<IDirect3DDevice9>::type espoir::DDevice::mD3Device;
//::_com_ptr_t<::_com_IIID<IDirect3DDevice9, &__uuidof(IDirect3DDevice9)>> espoir::DDevice::mD3Device;

HWND espoir::DDevice::hWnd = NULL;



void espoir::DDevice::SetHWND(HWND hWnd){

	//�ݒ肵�悤�Ƃ����E�B���h�E�n���h����NULL���ǂ���
	if(hWnd == NULL){
		DOut dout;
		dout << _T("Hwnd is null") << std::endl;
	}

	//�E�B���h�E�n���h���̐ݒ�
	DDevice::hWnd = hWnd;
}
bool espoir::DDevice::Init(){
		//�߂�l�@�������ɐ�������=true : ���s=false
		bool result = true;

		//DirectX�̊֐������s���ɔ��������G���[�R�[�h
		HRESULT err_code;

		//IDirect3D�I�u�W�F�N�g�C���X�^���X�̎擾
		mDirect3D.Attach( Direct3DCreate9(D3D_SDK_VERSION) );


		::D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		
		//�f�B�X���v�C���[�h�\����
		::D3DDISPLAYMODE d3ddm;
		ZeroMemory(&d3ddm, sizeof(d3ddm));

		//�f�B�X���v�C���[�h�̎擾
		err_code = mDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		//�f�B�X�v���C���[�h�擾���̃G���[�`�F�b�N
		if(FAILED(err_code)){
			espoir::DOut dout;
			dout << _T("GetAdapterDisplayMode�����s���܂���") << std::endl;
		}
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//d3ddm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = TRUE;


		//�C���X�^���X�n���h���̎擾
		HINSTANCE hInst = GetModuleHandle(NULL);

		//�C���X�^���X�n���h���擾���̃G���[�`�F�b�N
		if(!hInst){
			DOut dout;
			dout << _T("�C���X�^���X�n���h���̎擾�Ɏ��s���܂��� error: code") << std::endl;
			dout << GetLastError() << std::endl;
		}


		//�E�B���h�E�N���X���ƃE�B���h�E�̃^�C�g����
		String dClass = _T("espoir");
		String title = _T("Directx espoir");
		
		
		//�E�B���h�E�N���X�̓o�^
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= espoir::DWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInst;
		wcex.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_ESPOIR));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ESPOIR);
		wcex.lpszClassName	= dClass.c_str();
		wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		ATOM atom = RegisterClassEx(&wcex);


		//�v���O�����N�����̃I�v�V�����Ŏw�肳�ꂽ�E�B���h�E�̏�Ԃ��擾
		STARTUPINFO Info;
		GetStartupInfo(&Info);
		int nCmdShow = Info.wShowWindow;


		//���C���E�B���h�E�̐���
		hWnd = CreateWindow(dClass.c_str() , title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);
		
		//�R�}���h���C���̎擾
		LPTSTR cmd = GetCommandLine();

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		//���C���E�B���h�E�������̃G���[�`�F�b�N
		if(!hWnd){
			DOut dout;
			dout << _T("DirectX�AWindow�̐����Ɏ��s���܂���") << std::endl;
			dout << GetLastError() << std::endl;
		}

		//HEL(�\�t�g�E�F�A�G�~�����[�V����)�Ńf�o�C�X����
		HRESULT hResult;
		hResult = mDirect3D->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3Device);
		
		//�f�o�C�X�������̃G���[�`�F�b�N
		if(FAILED(hResult))
		{
			espoir::DOut dout;
			dout << _T("Error: HEL�ł̏������Ɏ��s���܂���") << std::endl;
			switch(hResult){
				case D3DERR_INVALIDCALL:
					dout << _T("���\�b�h�̌Ăяo���������B�p�����[�^�Ɉُ킩�������`�F�b�N���Ă�������") << std::endl;
					break;
				case D3DERR_NOTAVAILABLE:
					dout << _T("���̃f�o�C�X�́A�₢���킹���e�N�j�b�N���T�|�[�g���Ă��܂���") << std::endl;
					break;
				case D3DERR_OUTOFVIDEOMEMORY:
					dout << _T("Direct3D ���������s���̂ɏ\���ȃf�B�X�v���C ������������܂���") << std::endl;
					break;
			}
		}

		//DirectX�̏������Ɏ��s���Ă�����false��Ԃ�
		if(espoir::DDevice::mDirect3D == 0)
			result = false;

		return result;
}

LRESULT CALLBACK espoir::DWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch(message){

		//�E�B���h�E���j�����ꂽ
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		//�E�B���h�E���ĕ`�悳�ꂽ
		case WM_PAINT:
		
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}

void espoir::DDevice::DMainLoop(){
	
	//���b�Z�[�W
	MSG msg;
	
	//�C���X�^���X�n���h���̎擾
	HINSTANCE hInst = GetModuleHandle(NULL);
	
	//�A�N�Z�����[�^�i�V���[�g�J�b�g�L�[�j�e�[�u�����擾
	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_ESPOIR));

	// ���C�� ���b�Z�[�W ���[�v:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}