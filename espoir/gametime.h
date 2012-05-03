#pragma once


namespace espoir{

typedef DWORD DefaultRealType;


//ミリ秒から分に変換
template<typename RealType>
inline RealType ConvertMinutes(RealType milli) {
	return milli / 60;
}

//ミリ秒から時間に変換
template<typename RealType>
inline RealType ConvertHours(RealType milli) {
	return ConvertMinutes(milli) / 60;
}

//GetTickCountを使った測定
template<typename RealType = DefaultRealType>
class GameTime{
public:
	RealType startTime_;
	GameTime(){
		//システム起動時間。49日間経過すると0に戻る
		this->startTime_ = GetTickCount();
	}

	// アプリケーションを開始してからの時間を取得
	RealType GetStartTime() {
		return GetTickCount() - this->startTime_;
	}

};



}
