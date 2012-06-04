#include<iostream>
#include<vector>
#include<string>
#include<boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include"scenemanager.h"
#include"scene.h"



int main(int argc, char const* argv[])
{
	using std::cout;
	using std::endl;
	using std::vector;

	typedef std::string String;

	
	//Assignmentポリシーをはめ込む
	scene::SceneManager<EspoirSceneAssignment> sm;
	
	//ゲームループ機構
	//簡易テストなので無限ループにならないように回数を指定する
	for(int i = 0; i < 10; i++){
		sm.Draw();
		sm.Update();
	}




//smオブジェクトはDraw()とUpdate()しか呼び出すだけで
//次々ゲームのシーンが変わっていく！

//  というわけで下のようなコードを書く必要が無くなる
//    enum GameScene{
//        Title,
//        Battle,
//        ...色々なシーン
//        Ending,
//        TheEnd
//    };
//
//    GameScene gs = Title;
//    while(0)
//    {

//        switch(gs){
//            case Title:
//                DrawTitle();
//                UpdateTitle();
//                break;
//            case Battle:
//                DrawBattle();
//                UpdateBattle();
//                break;

//            ...シーンの数だけcaseを書く

//            case Ending:
//                DrawEnding();
//                UpdateEnding();
//                break;
//            case TheEnd:
//                DrawTheEnd();
//                UpdateTheEnd();
//                break;
//        }
//    }
	









//  オブジェクトの呼び出しを文字列で行なっているので
//  例えば
//  battle0
//  battle1
//  battle2
//  battle3
//とか連想配列にシーンクラスのオブジェクトがある場合
//  this->next_ = "battle" + 文字列変換関数(battleID);
// なんてことができる

	return 0;
}
