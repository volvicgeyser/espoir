#pragma once

namespace espoir{

template<class ObjType>
class DXInputDeviceCreation{
typedef boost::intrusive_ptr<ObjType> SPObjType;
public:
	static SPObjType Create(){

		//DirectInput8Device
		IDirectInputDevice8* tmp_dev;


		//DirectInput8Device
		const HRESULT devErr = sys::Input::GetInst()->CreateDevice(GUID_SysKeyboard,
				&tmp_dev, NULL);
		if(FAILED(devErr))
		{
			Stringstream ss;
#ifdef _DEBUG
			throw std::runtime_error("Device");
#else
			ss << _T("DirectInputDevice8 err=") << devErr;
#endif
			MessageBox(NULL, ss.str().c_str(), _T("err"), MB_OK);
		}
		
		SPObjType spInputDev = SPObjType(tmp_dev);

		//データフォーマット
		const HRESULT fmtErr = spInputDev->SetDataFormat(&c_dfDIKeyboard);

		const HRESULT coopErr = spInputDev->SetCooperativeLevel(sys::Form::GetInst()->GetHandle(),
				DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if(FAILED(coopErr)){
#ifdef _DEBUG
			throw std::runtime_error("協調レベルの設定に失敗");
#else
			MessageBox(NULL, _T("フォアグラウンド＆非排他モードの設定に失敗"),
					_T("err", MB_OK);
#endif
		}

		//入力制御開始
		spInputDev->Acquire();

		return spInputDev;

	}
};

}
