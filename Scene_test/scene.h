//-----------------------ここからはユーザー定義クラス-------------------------------------

//DefaultAbstractSceneを継承してシーンクラスを実装する場合、
//以下のものを実装する
//■メンバ関数
//+void Draw()　描画関数
//+void Update()　定期的に行う描画以外の処理関数
//+std::string GetScene() 自分自身のクラス名を表す任意の文字列を返す関数


//タイトル画面
class Title : public scene::DefaultAbstractScene{
public:
	void Draw(){
		std::cout << "Draw: --------------------" << std::endl;
		std::cout << "Draw: Titleシーンの描画"  << std::endl;
		std::cout << "Draw:・ニューゲーム" << std::endl;
		std::cout << "Draw:・セーブデータから" << std::endl;
		std::cout << "Draw:・オプション" << std::endl;
	}

	void Update(){
		std::cout << "Update: キーボード処理とか" << std::endl;
		std::cout << std::endl;

		//文字列で指定して次のシーンへ移行
		this->next_ = "battle";
	}

	std::string GetScene(){
		return std::string("title");
	}
	virtual ~Title(){}
};

//バトル画面
class Battle : public scene::DefaultAbstractScene{
public:

	Battle() : count_(0), hero(100, 50){}

	void Draw(){

		std::cout << "Draw: --------------------" << std::endl;
		std::cout << "Draw: Battleシーンの描画" << std::endl;

		//HPとかMPとかメニューの表示
		std::cout << "Draw: HP = " << this->hero.HP << std::endl;
		std::cout << "Draw: MP = " << this->hero.MP << std::endl;

		if(3 < this->count_){
			std::cout << "Draw: 大事なシーンなので" << this->count_ + 1 << "回描画しました" << std::endl;
		}
	}
	void Update(){
		std::cout << "Update: Battleシーン味方や敵の動きを定義したり…" << std::endl;
		std::cout << std::endl;

		//戦闘処理
		this->RecieveDamage(this->hero);
		this->UseSpell(this->hero);

		if(3 < this->count_)
			this->next_ = "ending";
		this->count_++;
	}

	std::string GetScene(){
		return std::string("battle");
	}

	virtual ~Battle(){}
private:
	int count_;

	struct Chara{
		Chara(int hp, int mp) : HP(hp), MP(mp){} 
		int HP;
		int MP;
	};
	
	Chara hero;

	//敵からのダメージ
	void RecieveDamage(Chara& c){
		c.HP -= 15;
	}

	//MP消費の呪文を使う
	void UseSpell(Chara& c){
		c.MP -= 3;
	}


};

//エンディング画面
class Ending : public scene::DefaultAbstractScene{
public:
	void Draw(){
		std::cout << "Draw: --------------------" << std::endl;
		std::cout << "Draw: エンディング" << std::endl;
	}
	void Update(){
		std::cout << "Update: Ending..." << std::endl;
		std::cout << std::endl;
		this->next_ = "theend";
	}
	std::string GetScene(){
		return std::string("ending");
	}
	virtual ~Ending(){}
};

//The end画面
class TheEnd : public scene::DefaultAbstractScene{
public:
	void Draw(){
		std::cout << "Draw: --------------------" << std::endl;
		std::cout << "Draw: ***********The End***************" << std::endl;
	}
	void Update(){
		std::cout << "Update: The End" << std::endl;
		std::cout << std::endl;
	}
	std::string GetScene(){
		return std::string("theend");
	}
	virtual ~TheEnd(){}
};

//連想配列の割り当てを行うクラスを定義する
template<class AbstractScene = scene::DefaultAbstractScene>
struct EspoirSceneAssignment
{
	typedef std::string KeyType;
	typedef boost::shared_ptr<AbstractScene> SPAbs;
	typedef boost::unordered_map<KeyType, SPAbs> Assoc;
	
	//ユーザーはこの関数をこの形で必ず実装しなければならない
	//戻り値: 最初に開始するシーンのKey
	//引数: 割り当てる連想配列
	static KeyType Assigne(Assoc& assoc){
		const std::string title("title");
		assoc[title] = SPAbs(new Title);
		assoc["battle"] = SPAbs(new Battle);
		assoc["ending"] = SPAbs(new Ending);
		assoc["theend"] = SPAbs(new TheEnd);
		//...
		//使うシーンクラスの数だけ書く

		return title;
	}

};


