#pragma once

//Factory�N���X�̃G���[�|���V�[
//�f�t�H���g�ł͗�O�𓊂���
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

//AbstractProduct  ���i�̊��N���X
//IdentifierType�@���iID�̌^(ex enum ProductId��std::string�Ȃǂ��킩��₷��)
//                �������Aenum�̏ꍇ�͂��Ƃ��琻�i�̎�ނ𑝂₷�Ƃ���enum�̗v�f��ǉ������Ԃ�������
//ProductCreator�@������0�Ő��i�̊��N���X�^��Ԃ��֐��|�C���^ AbstractProduct* f()
//                �H�����鎞�͐��i���w�肷��K�v�͖���
//ErrorPolicy�@�@�@�G���[���N�������Ƃ��̑Ώ��B�f�t�H���g�ł͗�O�𓊂���
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

	//���i�����ۂɍ��
	AbstractProduct* Create(const IdentifierType& id){
		typename AssocType::iterator it = this->assoc_.find(id);
		if(it != this->assoc_.end())
			return (it->second)();
		return OnUnknownType(id);
	}

	//�H��ō�����̂�o�^����i�����֐��̊֐��|�C���^��o�^����j
	void Register(const IdentifierType& id, ProductCreator creator){
		this->assoc_.insert(typename std::pair<IdentifierType, ProductCreator>(id, creator));
	}
	//���ɓo�^����Ă�����̂��H��ō��Ȃ��悤�ɂ���
	void Unregister(const IdentifierType& id){
		this->assoc_.erase(id);
	}
private:
	//�A�z�z��(Key = ���i��ID, value = �����֐��̊֐��|�C���^)
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
	//�L�����N�^�[�����H��
	Factory<AbstractChara, std::string> factory;

	//�H��Ŏ�舵�����i��o�^����
	factory.Register("enemy1", CharaCreatorFunc);

	//���ۂɍH��Ő��i�����
	AbstractChara* c = factory.Create("enemy1");


	//�A�b�v�L���X�g���Ĕh���N���X�̃����o���Ăяo��
	static_cast<Chara*>(c)->x  = 10;
	static_cast<Chara*>(c)->y  = 10;

	delete c;

	//�o�^����Ă��Ȃ����̂��Ăяo���Ɨ�O����������
//    factory.Create("�����̍H��ł͂��̐��i�͎�舵���Ă���܂���I");


	typedef boost::shared_ptr<AbstractChara> SPAbsChara;
	typedef std::vector<SPAbsChara> AbsCharaArray;

	AbsCharaArray v(30);
	
//    std::for_each(v.begin(), v.end(), Out() );
	std::for_each(v.begin(), v.end(), boost::bind(CharaCreate2<SPAbsChara>, _1, factory) );
//    std::for_each(v.begin(), v.end(), boost::bind(CharaCreate(), _1, factory) );
//    std::for_each(v.begin(), v.end(), what_type<SPAbsChara>);
	
	//�X�}�[�g�|�C���^�Ɋi�[
//    std::for_each(v.begin(), v.end(), boost::bind(Out_func<SPAbsChara>, _1));
    std::for_each(v.begin(), v.end(), Out_func<SPAbsChara>);
    boost::shared_ptr<AbstractChara> c2(factory.Create("enemy1"));
	

//    static_cast<Chara*>(c)


	std::cout << "Run" << std::endl;
	return 0;
}

#endif