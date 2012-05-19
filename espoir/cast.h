#pragma once

namespace espoir{

//型変換を許さない
//※if文のオーバーヘッドを伴う動的なチェック
//typeidが同じでも同じ型であることは保証されないことに注意
template<class To, class From>
inline To type_check(const From& f){
	if(typeid(From) != typeid(To))
		throw std::runtime_error("RistrictCastPolicy: 型の変換が許可されていません");
	return f;
}

//static_castを短くするだけ
template<class To, class From>
inline To cast(const From& f){
 	return static_cast<To>(f);
}

}