#pragma once


namespace espoir{

typedef DWORD DefaultRealType;


//�~���b���番�ɕϊ�
template<typename RealType>
inline RealType ConvertMinutes(RealType milli) {
	return milli / 60;
}

//�~���b���玞�Ԃɕϊ�
template<typename RealType>
inline RealType ConvertHours(RealType milli) {
	return ConvertMinutes(milli) / 60;
}

//GetTickCount���g��������
template<typename RealType = DefaultRealType>
class GameTime{
public:
	RealType startTime_;
	GameTime(){
		//�V�X�e���N�����ԁB49���Ԍo�߂����0�ɖ߂�
		this->startTime_ = GetTickCount();
	}

	// �A�v���P�[�V�������J�n���Ă���̎��Ԃ��擾
	RealType GetStartTime() {
		return GetTickCount() - this->startTime_;
	}

};



}
