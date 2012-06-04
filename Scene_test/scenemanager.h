#pragma once

namespace scene{
//-----------------------���C�u�����̗̈�-------------------------------------

//�|���V�[��SceneManager
//�Q�[����ʂ̐؂�ւ��Ɏg��
template<

	//�A�z�z��̊��蓖�Ă��s���N���X���w�肷��B
	//���[�U�[�͐ÓI�ȃ����o�֐�Assign����������K�v������B
	template<class> class Assignment,

	//���[�U�[����`�����V�[�����ۃN���X���w�肷��B
	class AbstractScene = DefaultAbstractScene
>
class SceneManager{
public:
	SceneManager()
	{
		this->current_ = Assignment<AbstractScene>::Assigne(this->strategy);
	}
	
	//�`�悷��
	void Draw(){
		strategy[this->current_]->Draw();
	}

	//�`��ȊO�̒���I�ȏ���
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


//�f�t�H���g�̒��ۃV�[���N���X
//���[�U�[�͂�����p�����ăV�[������������Ɗy
class DefaultAbstractScene{
public:
	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() = 0;

	//�`��ȊO�̍X�V����������
	virtual void Update() = 0;

	//���g�̃V�[�����擾
	virtual std::string GetScene() = 0;

	//���̃V�[����Ԃ�
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
