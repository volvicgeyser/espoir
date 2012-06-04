#pragma once

namespace scene{
//-----------------------ライブラリの領域-------------------------------------

//ポリシーなSceneManager
//ゲーム場面の切り替えに使う
template<

	//連想配列の割り当てを行うクラスを指定する。
	//ユーザーは静的なメンバ関数Assignを実装する必要がある。
	template<class> class Assignment,

	//ユーザーが定義したシーン抽象クラスを指定する。
	class AbstractScene = DefaultAbstractScene
>
class SceneManager{
public:
	SceneManager()
	{
		this->current_ = Assignment<AbstractScene>::Assigne(this->strategy);
	}
	
	//描画する
	void Draw(){
		strategy[this->current_]->Draw();
	}

	//描画以外の定期的な処理
	void Update(){
		strategy[this->current_]->Update();
		this->current_ = strategy[this->current_]->GetNextScene();
	}
private:
	typedef std::string KeyType;
	typedef boost::shared_ptr<AbstractScene> SPAbs;
	typedef boost::unordered_map<KeyType, SPAbs> Assoc;
	Assoc strategy;
	KeyType current_; 
};


//デフォルトの抽象シーンクラス
//ユーザーはこれを継承してシーンを実装すると楽
class DefaultAbstractScene{
public:
	//描画に関することを実装する
	virtual void Draw() = 0;

	//描画以外の更新を実装する
	virtual void Update() = 0;

	//自身のシーンを取得
	virtual std::string GetScene() = 0;

	//次のシーンを返す
	std::string GetNextScene()
	{
		if(this->next_.empty())
		{
			if(!this->GetScene().empty())
				return this->GetScene();
			else
				throw std::runtime_error("Self scene is empty.");
		}
		else
			return this->next_;
	}
	virtual ~DefaultAbstractScene(){};
protected:
	std::string next_;
};


}
