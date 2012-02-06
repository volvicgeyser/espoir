namespace espoir{



//静的ポリモーフィズム
//仮想関数によるオーバーヘッド無し

//デザインパターン
//Prototypeのインターフェース
template <class ChildClass>
struct IClonable{

	//Clone関数
	IClonable* Clone(){
		static_cast<ChildClass*>(this)->Clone();
	}
};


}