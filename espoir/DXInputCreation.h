#pragma once

//#include"system.h"
namespace espoir{
template<class ObjType>
class DXInputCreation {
	typedef boost::intrusive_ptr<IDirectInput8> SPObjType;
public:
	static SPObjType Create(){
		//DirectInput8
        IDirectInput8* tmp_input;

		const HINSTANCE hInst = GetModuleHandle(NULL);

		BOOST_ASSERT(hInst);

		const HRESULT inputErr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8,
				(void**)&tmp_input, NULL);

		if(FAILED(inputErr)){
#ifdef _DEBUG
			throw std::runtime_error("");
#else
			Stringstream ss;
			ss << _T("DirectInput8 err=") << inputErr;
			MessageBox(NULL, ss.str().c_str(),
					_T("err"), MB_OK);
#endif
		}

		BOOST_ASSERT(tmp_input);
		SPObjType spInput = SPObjType(tmp_input);


		return spInput;
			
	}

private:
};


}
