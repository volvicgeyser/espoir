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

	
	//Assignment�|���V�[���͂ߍ���
	scene::SceneManager<EspoirSceneAssignment> sm;
	
	//�Q�[�����[�v�@�\
	//�ȈՃe�X�g�Ȃ̂Ŗ������[�v�ɂȂ�Ȃ��悤�ɉ񐔂��w�肷��
	for(int i = 0; i < 10; i++){
		sm.Draw();
		sm.Update();
	}




//sm�I�u�W�F�N�g��Draw()��Update()�����Ăяo��������
//���X�Q�[���̃V�[�����ς���Ă����I

//  �Ƃ����킯�ŉ��̂悤�ȃR�[�h�������K�v�������Ȃ�
//    enum GameScene{
//        Title,
//        Battle,
//        ...�F�X�ȃV�[��
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

//            ...�V�[���̐�����case������

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
	









//  �I�u�W�F�N�g�̌Ăяo���𕶎���ōs�Ȃ��Ă���̂�
//  �Ⴆ��
//  battle0
//  battle1
//  battle2
//  battle3
//�Ƃ��A�z�z��ɃV�[���N���X�̃I�u�W�F�N�g������ꍇ
//  this->next_ = "battle" + ������ϊ��֐�(battleID);
// �Ȃ�Ă��Ƃ��ł���

	return 0;
}
