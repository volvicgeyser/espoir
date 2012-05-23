#pragma once

//Factoryクラスのエラーポリシー
//デフォルトでは例外を投げる
template<class IdentifierType, class ProductType>
struct DefaultFactoryError{
	struct Exception : public std::exception{
		const char* what() const throw(){
			return "Unknown object type passed to Factory.";
		}
	};
	static ProductType* OnUnknownType(IdentifierType){
		throw Exception();
	}
};

//AbstractProduct  製品の基底クラス
//IdentifierType　製品IDの型(ex enum ProductIdやstd::stringなどがわかりやすい)
//                ただし、enumの場合はあとから製品の種類を増やすときにenumの要素を追加する手間がかかる
//ProductCreator　引数が0で製品の基底クラス型を返す関数ポインタ AbstractProduct* f()
//                工場を作る時は製品を指定する必要は無い
//ErrorPolicy　　　エラーが起こったときの対処。デフォルトでは例外を投げる
template<
	class AbstractProduct,
	class IdentifierType,	
	class ProductCreator = AbstractProduct* (*)(),
	template<typename, class>
		class ErrorPolicy = DefaultFactoryError
>
class Factory;

template<
	class AbstractProduct,
	class IdentifierType,	
	class ProductCreator,
	template<typename, class>
		class ErrorPolicy
>
class Factory
 : public ErrorPolicy<IdentifierType, AbstractProduct>
{
	typedef	typename std::map<IdentifierType, ProductCreator> AssocType;
public:

	//製品を実際に作る
	AbstractProduct* Create(const IdentifierType& id){
		typename AssocType::iterator it = this->assoc_.find(id);
		if(it != this->assoc_.end())
			return (it->second)();
		return OnUnknownType(id);
	}

	//工場で作れるものを登録する（生成関数の関数ポインタを登録する）
	void Register(const IdentifierType& id, ProductCreator creator){
		this->assoc_.insert(typename std::pair<IdentifierType, ProductCreator>(id, creator));
	}
	//既に登録されているものを工場で作れないようにする
	void Unregister(const IdentifierType& id){
		this->assoc_.erase(id);
	}
private:
	//連想配列(Key = 製品のID, value = 生成関数の関数ポインタ)
	AssocType assoc_;
};


#ifdef OLD_CODE
//test----------------------------------------------------------------------
struct AbstractChara{
};
struct Chara : public AbstractChara{
	int x;
	int y;
};

class AbstractCreator{
public:
	int x;
	int y;
	virtual ~AbstractCreator(){}
	virtual AbstractChara* Create() = 0;
};
class CharaCreator : public AbstractCreator{
public:
	Chara* Create(){
		return new Chara();
	}
	Chara* operator()(){
		return new Chara();
	}
};

AbstractChara* AbsCharaCreatorFunc(){
	return new AbstractChara();
}

AbstractChara* CharaCreatorFunc(){
	return new Chara();
}


struct Out{
	template<typename T>
	void operator ()(T& t){
		std::cout << t << std::endl;	
	}
};

template<typename T>
void Out_func(T& t){
	std::cout << t << std::endl;	
}

struct CharaCreate{
	template<typename T>
	void operator ()(T& t, Factory<AbstractChara, std::string>& factory){
		t = T(factory.Create("enemy1"));
	}
};
template<typename T>
void CharaCreate2(T& t, Factory<AbstractChara, std::string>& factory){
	t = T(factory.Create("enemy1"));
}

int main(int argc, char const* argv[])
{
	//キャラクターを作る工場
	Factory<AbstractChara, std::string> factory;

	//工場で取り扱う製品を登録する
	factory.Register("enemy1", CharaCreatorFunc);

	//実際に工場で製品を作る
	AbstractChara* c = factory.Create("enemy1");


	//アップキャストして派生クラスのメンバを呼び出す
	static_cast<Chara*>(c)->x  = 10;
	static_cast<Chara*>(c)->y  = 10;

	delete c;

	//登録されていないものを呼び出すと例外が投げられる
//    factory.Create("うちの工場ではこの製品は取り扱っておりません！");


	typedef boost::shared_ptr<AbstractChara> SPAbsChara;
	typedef std::vector<SPAbsChara> AbsCharaArray;

	AbsCharaArray v(30);
	
//    std::for_each(v.begin(), v.end(), Out() );
	std::for_each(v.begin(), v.end(), boost::bind(CharaCreate2<SPAbsChara>, _1, factory) );
//    std::for_each(v.begin(), v.end(), boost::bind(CharaCreate(), _1, factory) );
//    std::for_each(v.begin(), v.end(), what_type<SPAbsChara>);
	
	//スマートポインタに格納
//    std::for_each(v.begin(), v.end(), boost::bind(Out_func<SPAbsChara>, _1));
    std::for_each(v.begin(), v.end(), Out_func<SPAbsChara>);
    boost::shared_ptr<AbstractChara> c2(factory.Create("enemy1"));
	

//    static_cast<Chara*>(c)


	std::cout << "Run" << std::endl;
	return 0;
}

#endif